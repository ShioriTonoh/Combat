// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/Notify/AnimNotifyState_TryTarget.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "FunctionLibrary/CombatGameplayStatics.h"
#include "GAS/CombatAbilitySystemComponent.h"

UAnimNotifyState_TryTarget::UAnimNotifyState_TryTarget()
{
	StartTryTargetEventTag = FGameplayTag::RequestGameplayTag(FName("Ability.Event.StartTryTarget"));
	StopTryTargetEventTag = FGameplayTag::RequestGameplayTag(FName("Ability.Event.StopTryTarget"));
}

void UAnimNotifyState_TryTarget::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (MeshComp)
	{
		if (auto OwnerActor = MeshComp->GetOwner())
		{
			if (bOverrideEffectCauser)
			{
				OwnerActor = OwnerActor->GetOwner();
			}

			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, StartTryTargetEventTag, 
				UCombatGameplayStatics::MakeGameplayEventDataFromTargetActorParam(OwnerActor, TryTargetParam, MeshComp->GetOwner()));
		}
	}
}

void UAnimNotifyState_TryTarget::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (MeshComp)
	{
		if (auto OwnerActor = MeshComp->GetOwner())
		{
			if (bOverrideEffectCauser)
			{
				OwnerActor = OwnerActor->GetOwner();
			}

			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, StopTryTargetEventTag, FGameplayEventData());
		}
	}
}
