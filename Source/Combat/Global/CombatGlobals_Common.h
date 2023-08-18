// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "Combat.h"
#include "CombatGlobals_Common.generated.h"

/**
 * Ability Input ID
 */
UENUM(BlueprintType)
enum class ECombatInputID : uint8
{
	None			UMETA(DisplayName = "None"),
	Move			UMETA(DisplayName = "Move"),
	Look			UMETA(DisplayName = "Look"),
	Jump			UMETA(DisplayName = "Jump"),
	Dash			UMETA(DisplayName = "Dash"),
	Lock			UMETA(DisplayName = "Lock"),
	LightAttack		UMETA(DisplayName = "LightAttack"),
	HeavyAttack		UMETA(DisplayName = "HeavyAttack"),
	Avoid			UMETA(DisplayName = "Avoid"),
	GuardPoint		UMETA(DisplayName = "GuardPoint")
};

/**
 * 
 */
UCLASS()
class COMBAT_API UCombatGlobals_Ability : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	
};
