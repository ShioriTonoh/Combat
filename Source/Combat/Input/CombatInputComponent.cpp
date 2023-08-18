// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/CombatInputComponent.h"
#include "Game/Character/CombatPlayerCharacter.h"

UCombatInputComponent::UCombatInputComponent(const FObjectInitializer& ObjectInitializer)
{
}

void UCombatInputComponent::AddInputMappings(const UInputMappingContext* MappingContext, int32 newPriority) const
{
	if (ACombatPlayerCharacter* Player = Cast<ACombatPlayerCharacter>(GetOwner()))
	{
		if (APlayerController* PC = Cast<APlayerController>(Player->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* EILPSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
			{
				EILPSubSystem->AddMappingContext(MappingContext, newPriority);
			}
		}
	}
}

void UCombatInputComponent::RemoveInputMappings(const UInputMappingContext* MappingContext) const
{
	if (ACombatPlayerCharacter* Player = Cast<ACombatPlayerCharacter>(GetOwner()))
	{
		if (APlayerController* PC = Cast<APlayerController>(Player->GetController()))
		{
			if (UEnhancedInputLocalPlayerSubsystem* EILPSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
			{
				EILPSubSystem->RemoveMappingContext(MappingContext);
			}
		}
	}
}
