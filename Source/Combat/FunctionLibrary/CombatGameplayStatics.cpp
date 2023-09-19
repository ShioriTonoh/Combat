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

FGameplayEventData UCombatGameplayStatics::MakeGameplayEventDataFromTargetActorParam(AActor* Actor, const FCombatTargetActorParam& InTargetActorParam, AActor* OptionalEffectCauser)
{
	FGameplayEventData NewData;

	if (const auto ASC = UCombatGameplayStatics::GetAbilitySystemComponent(Actor))
	{
		NewData.Instigator = Actor;
		NewData.ContextHandle = ASC->MakeEffectContext();
		NewData.ContextHandle.AddInstigator(Actor, OptionalEffectCauser);
		//StaticCast<FCombatGameplayEffectContext*>(NewData.ContextHandle.Get())->TargetActorParam = InTargetActorParam;
	}

	return NewData;
}

void UCombatGameplayStatics::GetTargetActorParamFromGameplayEventData(const FGameplayEventData& EventData, FCombatTargetActorParam& OutTargetActorParam)
{
	if (EventData.ContextHandle.IsValid())
	{
		//OutTargetActorParam = StaticCast<const FCombatGameplayEffectContext*>(EventData.ContextHandle.Get())->TargetActorParam;
	}
}
