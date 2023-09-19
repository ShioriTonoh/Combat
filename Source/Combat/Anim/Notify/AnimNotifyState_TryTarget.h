// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"
#include "Global/CombatGlobals_Common.h"
#include "AnimNotifyState_TryTarget.generated.h"

/**
 * 
 */
UCLASS()
class COMBAT_API UAnimNotifyState_TryTarget : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UAnimNotifyState_TryTarget();

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTag StartTryTargetEventTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTag StopTryTargetEventTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	bool bOverrideEffectCauser;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimNotify")
	FCombatTargetActorParam TryTargetParam;
};
