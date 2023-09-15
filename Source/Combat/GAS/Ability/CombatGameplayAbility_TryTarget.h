// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Ability/CombatGameplayAbility.h"
#include "CombatGameplayAbility_TryTarget.generated.h"

/**
 * 
 */
UCLASS()
class COMBAT_API UCombatGameplayAbility_TryTarget : public UCombatGameplayAbility
{
	GENERATED_BODY()

public:
	UCombatGameplayAbility_TryTarget();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTag StopTryTargetEventTag;

	UPROPERTY(Transient, BlueprintReadOnly)
	TWeakObjectPtr<class AGameplayAbilityTargetActor> SpawnedActor;
};
