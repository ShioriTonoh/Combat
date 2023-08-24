// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CombatGameplayAbility.generated.h"

enum class ECombatInputID : uint8;

/**
 * Gameplay Ability base class
 */
UCLASS()
class COMBAT_API UCombatGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UCombatGameplayAbility();

	FORCEINLINE ECombatInputID GetAbilityBoundInputID() const { return InputID; }

protected:
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	/* Only fill this when this ability can be activated by player input, passive ability and enemy specific ability should set this value to None */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AbilityDefaults")
	ECombatInputID InputID;

	/* Passive ability can't be triggered by player Input or AI controller */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AbilityDefaults")
	bool bPassive;

	/* Decide which ability to activate by AI controller or when multiple abilities bound to same InputID */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AbilityDefaults")
	int32 Priority;

	// TODO: Don't expose this value to blueprint until start working on cost and cooldown 
	// UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AbilityDefaults")
	bool bCommitAbilityOnActivation;

	/* try to activate this ability immediately when Avatar set */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AbilityDefaults")
	bool bActivateAbilityOnGranted;

	/* Gameplay events should be sent to self when this ability activate */
	UPROPERTY(EditDefaultsOnly, Category = "Tags|Custom")
	FGameplayTagContainer SelfEventTagOnActivate;

	/* Gameplay events should be sent to self when this ability end */
	UPROPERTY(EditDefaultsOnly, Category = "Tags|Custom")
	FGameplayTagContainer SelfEventTagOnEnd;
};
