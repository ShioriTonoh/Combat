// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/CombatGameplayAbility.h"
#include "GAS/CombatAbilitySystemComponent.h"
#include "Global/CombatGlobals_Common.h"

UCombatGameplayAbility::UCombatGameplayAbility()
	: InputID(ECombatInputID::None)
	, bPassive(false)
	, Priority(0)
	, bCommitAbilityOnActivation(false)
	, bActivateAbilityOnGranted(false)
{
}

void UCombatGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (bActivateAbilityOnGranted)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

bool UCombatGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UCombatGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (bCommitAbilityOnActivation)
	{
		CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo);
	}
		
	for (const FGameplayTag& Tag : SelfEventTagOnActivate)
	{
		SendGameplayEvent(Tag, FGameplayEventData());
	}

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UCombatGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	for (const FGameplayTag& Tag : SelfEventTagOnEnd)
	{
		SendGameplayEvent(Tag, FGameplayEventData());
	}

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
