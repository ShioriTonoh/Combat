// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CombatGameplayStatics.generated.h"

/**
 * 
 */
UCLASS()
class COMBAT_API UCombatGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Ability", meta = (WorldContext = "WorldContextObject"))
	static class UCombatGlobals_Ability* GetCombatAbilityGlobals(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Ability")
	static class UCombatAbilitySystemComponent* GetAbilitySystemComponent(const AActor* Actor);

	UFUNCTION(BlueprintPure, Category = "Ability")
	static FGameplayEventData MakeGameplayEventDataFromTargetActorClass(AActor* Actor,TSubclassOf<class ACombatGameplayAbilityTargetActor> InTargetActorClass, AActor* OptionalEffectCauser = nullptr);
};
