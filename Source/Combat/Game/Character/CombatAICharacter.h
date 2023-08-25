// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BehaviorTree.h"
#include "CoreMinimal.h"
#include "Game/Character/CombatCharacterBase.h"
#include "CombatAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class COMBAT_API ACombatAICharacter : public ACombatCharacterBase
{
	GENERATED_BODY()
	
public:

	FORCEINLINE class UBehaviorTree* GetBehaviorTree() const
	{
		return BehaviorTree;
	}

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Behavior")
	TObjectPtr<class UBehaviorTree> BehaviorTree;

	UPROPERTY(Transient)
	TObjectPtr<class ACombatAIController> AIController;
};
