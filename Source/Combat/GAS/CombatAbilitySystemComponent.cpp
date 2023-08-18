// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/CombatAbilitySystemComponent.h"

void UCombatAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCombatAbilitySystemComponent::InitDefaultAbilities(TArray<TSubclassOf<UCombatGameplayAbility>> InActiveAbilities, TArray<TSubclassOf<UCombatGameplayAbility>> InPassiveAbilities)
{
	if (bCharacterAbilitiesGiven)
		return;

	if (InPassiveAbilities.Num() > 0)
		InActiveAbilities.Append(InPassiveAbilities);

	for (TSubclassOf<UJadeGameplayAbility>& Ability : InActiveAbilities)
	{
		if (!Ability)
			continue;

		auto AbilityHandle = GiveAbility(FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), GetOwnerActor()));

		ActiveAbilityHandles.Emplace(AbilityHandle);
	}
}
