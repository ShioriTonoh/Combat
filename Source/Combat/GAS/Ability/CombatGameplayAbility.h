// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CombatGameplayAbility.generated.h"

enum class ECombatInputID : uint8;

/**
 * 
 */
UCLASS()
class COMBAT_API UCombatGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UCombatGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "AbilityDefaults")
	ECombatInputID InputID;
};
