// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/CombatGameplayStatics.h"
#include "AbilitySystemGlobals.h"
#include "Kismet/GameplayStatics.h"
#include "GAS/CombatAbilitySystemComponent.h"

UCombatGlobals_Ability* UCombatGameplayStatics::GetCombatAbilityGlobals(const UObject* WorldContextObject)
{
	return nullptr;
}

UCombatAbilitySystemComponent* UCombatGameplayStatics::GetAbilitySystemComponent(const AActor* Actor)
{
	return Cast<UCombatAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor, false));
}
