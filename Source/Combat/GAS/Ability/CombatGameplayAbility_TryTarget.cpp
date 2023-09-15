// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Ability/CombatGameplayAbility_TryTarget.h"

UCombatGameplayAbility_TryTarget::UCombatGameplayAbility_TryTarget()
{
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = FGameplayTag::RequestGameplayTag(FName("Ability.Event.StartTryTarget"));
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;

	StopTryTargetEventTag = FGameplayTag::RequestGameplayTag(FName("Ability.Event.StopTryTarget"));
}

void UCombatGameplayAbility_TryTarget::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (TriggerEventData)
	{
	}
	else
	{
		//EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}

void UCombatGameplayAbility_TryTarget::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
