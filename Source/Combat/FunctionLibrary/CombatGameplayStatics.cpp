// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/CombatGameplayStatics.h"
#include "AbilitySystemGlobals.h"
#include "Kismet/GameplayStatics.h"
#include "GAS/CombatAbilitySystemComponent.h"
#include "Global/CombatGlobals_Common.h"

UCombatGlobals_Ability* UCombatGameplayStatics::GetCombatAbilityGlobals(const UObject* WorldContextObject)
{
	return nullptr;
}

UCombatAbilitySystemComponent* UCombatGameplayStatics::GetAbilitySystemComponent(const AActor* Actor)
{
	return Cast<UCombatAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor, false));
}

FGameplayEventData UCombatGameplayStatics::MakeGameplayEventDataFromTargetActorClass(AActor* Actor, TSubclassOf<class ACombatGameplayAbilityTargetActor> InTargetActorClass, AActor* OptionalEffectCauser)
{
	FGameplayEventData NewData;

	if (const auto ASC = UCombatGameplayStatics::GetAbilitySystemComponent(Actor))
	{
		NewData.Instigator = Actor;
		NewData.ContextHandle = ASC->MakeEffectContext();
		NewData.ContextHandle.AddInstigator(Actor, OptionalEffectCauser);
		StaticCast<FCombatGameplayEffectContext*>(NewData.ContextHandle.Get())->TargetActorClass = InTargetActorClass;
	}

	return NewData;
}
