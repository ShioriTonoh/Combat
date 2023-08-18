// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CombatAbilitySystemComponent.generated.h"

class UCombatGameplayAbility;

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
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UCombatGameplayAbility>> ActiveAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UCombatGameplayAbility>> PassiveAbilities;

private:
	bool bCharacterAbilitiesGiven;

	UPROPERTY(Transient)
	TArray<FGameplayAbilitySpecHandle> ActiveAbilityHandles;
};
