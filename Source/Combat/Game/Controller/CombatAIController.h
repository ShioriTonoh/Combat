// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CombatAIController.generated.h"

/**
 * 
 */
UCLASS()
class COMBAT_API ACombatAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ACombatAIController(const FObjectInitializer& ObjectInitializer);

	virtual void SetupBehaviorTree(class UBehaviorTree* InBehaviorTreePtr);
	virtual void RunBehavior() const;
	virtual void StopBehavior() const;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY(Transient)
	TObjectPtr<class UBehaviorTreeComponent> BehaviorTreeComp;
	
	UPROPERTY(Transient)
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(Transient)
	TWeakObjectPtr<class ACombatAICharacter> PossessedCharacter;
};
