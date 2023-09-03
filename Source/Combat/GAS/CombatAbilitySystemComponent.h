// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CombatAbilitySystemComponent.generated.h"

class UCombatGameplayAbility;
class UAnimMontage;

/**
 * Base ASC class
 */
UCLASS()
class COMBAT_API UCombatAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	void InitDefaultAbilities(TArray<TSubclassOf<UCombatGameplayAbility>> InActiveAbilities, TArray<TSubclassOf<UCombatGameplayAbility>> InPassiveAbilities = TArray<TSubclassOf<UCombatGameplayAbility>>());

protected:
	/* Abilities that can be triggered by player input or AI controller*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UCombatGameplayAbility>> ActiveAbilities;

	/* Abilities that can be triggered only by events */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UCombatGameplayAbility>> PassiveAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TObjectPtr<UAnimMontage>> AttackAnimMontage;

private:
	bool bCharacterAbilitiesGiven;
};
