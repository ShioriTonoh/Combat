// Copyright Epic Games, Inc. All Rights Reserved.

#include "CombatPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Game/Character/CombatAICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/CombatAbilitySystemComponent.h"
#include "Input/CombatInputComponent.h"
#include "Kismet/KismetMathLibrary.h"


//////////////////////////////////////////////////////////////////////////
// ACombatPlayerCharacter

ACombatPlayerCharacter::ACombatPlayerCharacter()
	: LockSphereRadius(500.f)
	, bIsLockingTarget(false)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	AbilitySystemComponent = CreateDefaultSubobject<UCombatAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	check(AbilitySystemComponent);

	CombatInputComponent = CreateDefaultSubobject<UCombatInputComponent>(TEXT("InputComponent"));
	check(CombatInputComponent);
}

void ACombatPlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 1);
		}
	}
}

void ACombatPlayerCharacter::Tick(float DeltaTime)
{
	if (bIsLockingTarget)
	{
		SetCameraRotationToLockTarget();
	}
}

void ACombatPlayerCharacter::BindASCInput()
{
	if (IsValid(AbilitySystemComponent) && IsValid(InputComponent))
	{
		if (APlayerController* PC = CastChecked<APlayerController>(GetController()))
		{
			TArray<uint32> BindHandles;
			CombatInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::OnAbilityInputPressed, &ThisClass::OnAbilityInputReleased, /*out*/ BindHandles);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACombatPlayerCharacter::FindLockTarget()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		TArray<FOverlapResult> OverlapResults;
		GetWorld()->OverlapMultiByChannel(OverlapResults, GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(LockSphereRadius), QueryParams);

		float MinDist = 9999.f;

		for (auto OverlapResult : OverlapResults)
		{
			if (ACombatAICharacter* NewTarget = Cast<ACombatAICharacter>(OverlapResult.GetActor()))
			{
				FVector2D Vec;
				if (PC->ProjectWorldLocationToScreen(NewTarget->GetActorLocation(), Vec))
				{
					FVector ToPendingTarget = NewTarget->GetActorLocation() - GetActorLocation();
					ToPendingTarget.Z = 0.f;

					if (MinDist > ToPendingTarget.Size())
					{
						MinDist = ToPendingTarget.Size();
						CurrentLockTarget = NewTarget;
					}
				}
			}
		}
	}
	else
	{
		CurrentLockTarget = nullptr;
	}

}

void ACombatPlayerCharacter::TryLockTarget()
{
	if (bIsLockingTarget)
	{
		CancelLockTarget();
	}
	else
	{
		DoLockTarget();
	}
}

void ACombatPlayerCharacter::DoLockTarget()
{
	FindLockTarget();
	bIsLockingTarget = true;
	bUseControllerRotationYaw = true;
}

void ACombatPlayerCharacter::CancelLockTarget()
{
	CurrentLockTarget = nullptr;
	bIsLockingTarget = false;
	bUseControllerRotationYaw = false;
}

void ACombatPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind native input
	if (UCombatInputComponent* IC = CastChecked<UCombatInputComponent>(PlayerInputComponent)) 
	{
		IC->BindNativeAction(InputConfig, ECombatInputID::Look, ETriggerEvent::Triggered, this, &ThisClass::Look, false);
		IC->BindNativeAction(InputConfig, ECombatInputID::Move, ETriggerEvent::Triggered, this, &ThisClass::Move, false);
		IC->BindNativeAction(InputConfig, ECombatInputID::Lock, ETriggerEvent::Started, this, &ThisClass::TryLockTarget, false);
	}

	BindASCInput();
}

void ACombatPlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACombatPlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACombatPlayerCharacter::OnAbilityInputPressed(const ECombatInputID InputID)
{
	AbilitySystemComponent->PressInputID(StaticCast<int32>(InputID));
}

void ACombatPlayerCharacter::OnAbilityInputReleased(const ECombatInputID InputID)
{
	AbilitySystemComponent->ReleaseInputID(StaticCast<int32>(InputID));
}

void ACombatPlayerCharacter::SetCameraRotationToLockTarget()
{
	if (GetController())
	{
		if (CurrentLockTarget.IsValid())
		{
			FRotator NewControlRotation = UKismetMathLibrary::FindLookAtRotation(GetPawnViewLocation(), CurrentLockTarget->GetActorLocation());
			FVector ToTargetVector = CurrentLockTarget->GetActorLocation() - GetActorLocation();
			GetController()->SetControlRotation(NewControlRotation);
		}
		else
		{
			GetController()->SetControlRotation(GetActorRotation());
			CancelLockTarget();
		}
	}

}
