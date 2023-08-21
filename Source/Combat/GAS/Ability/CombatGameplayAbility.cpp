// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Ability/CombatGameplayAbility.h"

UCombatGameplayAbility::UCombatGameplayAbility()
{
}

void UCombatGameplayAbility::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	if (ActorInfo != NULL && ActorInfo->AvatarActor != NULL)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
	}
}
