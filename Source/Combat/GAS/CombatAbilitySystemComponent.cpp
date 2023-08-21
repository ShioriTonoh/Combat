// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/CombatAbilitySystemComponent.h"
#include "GAS/Ability/CombatGameplayAbility.h"
#include "Global/CombatGlobals_Common.h"

void UCombatAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	InitDefaultAbilities(ActiveAbilities, PassiveAbilities);
}

void UCombatAbilitySystemComponent::InitDefaultAbilities(TArray<TSubclassOf<UCombatGameplayAbility>> InActiveAbilities, TArray<TSubclassOf<UCombatGameplayAbility>> InPassiveAbilities)
{
	if (bCharacterAbilitiesGiven)
	{
		return;
	}

	if (InPassiveAbilities.Num() > 0)
	{
		InActiveAbilities.Append(InPassiveAbilities);
	}

	for (TSubclassOf<UCombatGameplayAbility>& Ability : InActiveAbilities)
	{
		if (Ability)
		{
			GiveAbility(FGameplayAbilitySpec(Ability, 1, StaticCast<int32>(Ability.GetDefaultObject()->GetAbilityBoundInputID()), GetOwnerActor()));
		}
	}

	bCharacterAbilitiesGiven = true;
}
