// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Character/CombatCharacterBase.h"
#include "GAS/CombatAbilitySystemComponent.h"

// Sets default values
ACombatCharacterBase::ACombatCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACombatCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	GenerateWeapon();
}

void ACombatCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}	
}

// Called every frame
void ACombatCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACombatCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* ACombatCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

bool ACombatCharacterBase::GenerateWeapon()
{
	if (WeaponClass)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		WeaponInstance = GetWorld()->SpawnActor<AActor>(WeaponClass, SpawnParameters);

		UpdateWeaponPosition(false);

		return IsValid(WeaponInstance);
	}
	return false;
}

void ACombatCharacterBase::UpdateWeaponPosition(bool bUseCombatSocket)
{
	if (IsValid(WeaponInstance))
	{
		const FName& SocketName = bUseCombatSocket ? WeaponSocket_Combat : WeaponSocket_Idle;
		WeaponInstance->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	}
}

