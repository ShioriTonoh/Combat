// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/Notify/AnimNotifyState_ModifyTag.h"
#include "FunctionLibrary/CombatGameplayStatics.h"
#include "GAS/CombatAbilitySystemComponent.h"

void UAnimNotifyState_ModifyTag::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (IsValid(MeshComp))
	{
		UCombatAbilitySystemComponent* OwnerASC = UCombatGameplayStatics::GetAbilitySystemComponent(MeshComp->GetOwner());
		
		if (IsValid(OwnerASC))
		{
			if (!MeshComp_NotifyBeginExecuted.Contains(MeshComp))
			{
				OwnerASC->AddLooseGameplayTags(AddTags);
				MeshComp_NotifyBeginExecuted.Add(MeshComp);
			}
		}
	}
}

void UAnimNotifyState_ModifyTag::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (IsValid(MeshComp))
	{
		UCombatAbilitySystemComponent* OwnerASC = UCombatGameplayStatics::GetAbilitySystemComponent(MeshComp->GetOwner());
		
		if (IsValid(OwnerASC))
		{
			if (MeshComp_NotifyBeginExecuted.Contains(MeshComp))
			{
				OwnerASC->RemoveLooseGameplayTags(AddTags);
				MeshComp_NotifyBeginExecuted.Remove(MeshComp);
			}
		}
	}
}
