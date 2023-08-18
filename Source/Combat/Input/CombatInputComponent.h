// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Input/CombatInputConfig.h"
#include "CombatInputComponent.generated.h"

/**
 * Combat Input component
 */
UCLASS()
class COMBAT_API UCombatInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	UCombatInputComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category="EnhancedInput")
	void AddInputMappings(const UInputMappingContext* MappingContext, int32 newPriority = 200) const;
	UFUNCTION(BlueprintCallable, Category = "EnhancedInput")
	void RemoveInputMappings(const UInputMappingContext* MappingContext) const;

	template<class UserClass, typename FuncType>
	void BindNativeAction(const UCombatInputConfig* InputConfig, const ECombatInputID InputID, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound);

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAbilityActions(const UCombatInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles);
};

template<class UserClass, typename FuncType>
inline void UCombatInputComponent::BindNativeAction(const UCombatInputConfig* InputConfig, const ECombatInputID InputID, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, bool bLogIfNotFound)
{
	check(InputConfig);
	if (const UInputAction* IA = InputConfig->FindNativeInputActionForInputID(InputID, bLogIfNotFound))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
}

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
inline void UCombatInputComponent::BindAbilityActions(const UCombatInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles)
{
	check(InputConfig);

	for (const FCombatInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction)
		{
			if (PressedFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputID).GetHandle());
			}

			if (ReleasedFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputID).GetHandle());
			}
		}
	}
}
