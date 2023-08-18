// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/CombatInputConfig.h"

UCombatInputConfig::UCombatInputConfig(const FObjectInitializer& ObjectInitializer)
{
}

const UInputAction* UCombatInputConfig::FindNativeInputActionForInputID(const ECombatInputID InputID, bool bLogNotFound) const
{
	for (const FCombatInputAction& Action : NativeInputActions)
	{
		if (Action.InputAction && (Action.InputID == InputID))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogCombat, Error, TEXT("Can't find NativeInputAction for InputID [%s] on InputConfig [%s]."), *UEnum::GetValueAsString(InputID), *GetNameSafe(this));
	}
	return nullptr;
}

const UInputAction* UCombatInputConfig::FindAbilityInputActionForInputID(const ECombatInputID InputID, bool bLogNotFound) const
{
	for (const FCombatInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && (Action.InputID == InputID))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogCombat, Error, TEXT("Can't find AbilityInputAction for InputID [%s] on InputConfig [%s]."), *UEnum::GetValueAsString(InputID), *GetNameSafe(this));
	}

	return nullptr;
}
