// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Global/CombatGlobals_Common.h"
#include "CombatInputConfig.generated.h"

class UInputAction;

/**
 * FCombatInputAction
 *
 * Struct used to map a input action to a gameplay enum.
 */
USTRUCT(BlueprintType)
struct FCombatInputAction
{
	GENERATED_BODY()

	FCombatInputAction()
	: InputAction(nullptr)
	, InputID(ECombatInputID::None)
	{
		
	}

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction;

	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "EnhancedInput"))
	ECombatInputID InputID;
};

/**
 * 
 */
UCLASS()
class COMBAT_API UCombatInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UCombatInputConfig(const FObjectInitializer& ObjectInitializer);

	const UInputAction* FindNativeInputActionForInputID(const ECombatInputID InputID, bool bLogNotFound = true) const;
	const UInputAction* FindAbilityInputActionForInputID(const ECombatInputID InputID, bool bLogNotFound = true) const;

	public:
	// List of input actions used by the owner.  These input actions are mapped to a gameplay tag and must be manually bound.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FCombatInputAction> NativeInputActions;

	// List of input actions used by the owner.  These input actions are mapped to a gameplay tag and are automatically bound to abilities with matching input tags.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FCombatInputAction> AbilityInputActions;
};
