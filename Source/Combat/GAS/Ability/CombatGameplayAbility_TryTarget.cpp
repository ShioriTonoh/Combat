// Fill out your copyright notice in the Description page of Project Settings.

#include "GAS/Ability/CombatGameplayAbility_TryTarget.h"
#include "Abilities/Tasks/AbilityTask_WaitTargetData.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "FunctionLibrary/CombatGameplayStatics.h"
#include "Game/Character/CombatAICharacter.h"
#include "Game/Character/CombatPlayerCharacter.h"
#include "GAS/TargetActor/CombatGameplayAbilityTargetActor.h"
#include "Global/CombatGlobals_Common.h"

UCombatGameplayAbility_TryTarget::UCombatGameplayAbility_TryTarget()
{
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerTag = FGameplayTag::RequestGameplayTag(FName("Ability.Event.StartTryTarget"));
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;

	StopTryTargetEventTag = FGameplayTag::RequestGameplayTag(FName("Ability.Event.StopTryTarget"));
}

void UCombatGameplayAbility_TryTarget::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	bIsPlayerTryingTarget = ActorInfo->AvatarActor->IsA(ACombatPlayerCharacter::StaticClass());
	
	if (TriggerEventData)
	{
		FCombatTargetActorParam NewParam;
		UCombatGameplayStatics::GetTargetActorParamFromGameplayEventData(*TriggerEventData, NewParam);

		if (NewParam.TargetActorClass == nullptr)
		{
			NewParam = DefaultParam;

			//EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
			//return;
		}

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = GetCurrentActorInfo()->AvatarActor.Get();

		AGameplayAbilityTargetActor* SpawnedTargetActor = Cast<AGameplayAbilityTargetActor>(GetWorld()->SpawnActor(NewParam.TargetActorClass, &FVector::ZeroVector, &FRotator::ZeroRotator, SpawnParameters));

		const auto TargetTask = UAbilityTask_WaitTargetData::WaitTargetDataUsingActor(this, 
																			NewParam.TaskInstanceName, 
																			EGameplayTargetingConfirmation::UserConfirmed, 
																			SpawnedTargetActor);
		TargetTask->ValidData.AddDynamic(this, &ThisClass::OnValidDataCallback);

		if (!IsValid(SpawnedTargetActor))
		{
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
			return;
		}
		TargetTask->ReadyForActivation();

		SpawnedActor = Cast<ACombatGameplayAbilityTargetActor>(SpawnedTargetActor);
		SpawnedActor->StartTargetingWithNewParam(this, NewParam);

		const auto EndAbilityTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, StopTryTargetEventTag);
		EndAbilityTask->EventReceived.AddDynamic(this, &ThisClass::OnEventRecieved);
		EndAbilityTask->ReadyForActivation();
	}
	else
	{
		//EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}

void UCombatGameplayAbility_TryTarget::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UCombatGameplayAbility_TryTarget::OnValidDataCallback(const FGameplayAbilityTargetDataHandle& Data)
{
	if (bIsPlayerTryingTarget)
	{
		for (const auto Actor : UAbilitySystemBlueprintLibrary::GetAllActorsFromTargetData(Data))
		{
			if (ACombatAICharacter* Enemy = Cast<ACombatAICharacter>(Actor))
			{
				FGameplayEventData NewEvent;
				NewEvent.EventTag = FGameplayTag::RequestGameplayTag(FName("Ability.Event.KnockHit"));
				//NewEvent.TargetTags = SpawnedActor->GetTargetActorParam().AdditionalTagToTarget;
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Enemy, NewEvent.EventTag, NewEvent);
			}
		}
	}
	else
	{
		for (const auto Actor : UAbilitySystemBlueprintLibrary::GetAllActorsFromTargetData(Data))
		{
			if (ACombatPlayerCharacter* Player = Cast<ACombatPlayerCharacter>(Actor))
			{
				FGameplayEventData NewEvent;
				NewEvent.EventTag = FGameplayTag::RequestGameplayTag(FName("Ability.Event.KnockHit"));
				//NewEvent.TargetTags = SpawnedActor->GetTargetActorParam().AdditionalTagToTarget;
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Player, NewEvent.EventTag, NewEvent);
			}
		}
	}

}

void UCombatGameplayAbility_TryTarget::OnEventRecieved(FGameplayEventData EventData)
{
	if (StopTryTargetEventTag == EventData.EventTag)
	{
		SpawnedActor = nullptr;
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
	}
}
