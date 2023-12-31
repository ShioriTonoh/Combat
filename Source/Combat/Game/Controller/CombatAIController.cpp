// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Controller/CombatAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Game/Character/CombatAICharacter.h"
#include "Perception/AIPerceptionComponent.h"

ACombatAIController::ACombatAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BrainComponent = BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	check(BehaviorTreeComp);

	bAttachToPawn = true;

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	check(PerceptionComponent);
}

void ACombatAIController::SetupBehaviorTree(UBehaviorTree* InBehaviorTreePtr)
{
	if (IsValid(InBehaviorTreePtr))
	{
		BehaviorTree = InBehaviorTreePtr;
		UseBlackboard(BehaviorTree->BlackboardAsset, StaticCast<UBlackboardComponent*&>(Blackboard));
	}
}

void ACombatAIController::RunBehavior() const
{
	if (IsValid(BehaviorTreeComp) && IsValid(BehaviorTree))
	{
		BehaviorTreeComp->StartTree(*BehaviorTree);
	}
}

void ACombatAIController::StopBehavior() const
{
	if (IsValid(BehaviorTreeComp) && IsValid(BehaviorTree))
	{
		BehaviorTreeComp->StopTree();
	}
}

void ACombatAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedCharacter = Cast<ACombatAICharacter>(InPawn);
}

void ACombatAIController::OnUnPossess()
{
	Super::OnUnPossess();

	BehaviorTreeComp = nullptr;
	BehaviorTree = nullptr;
	BrainComponent = nullptr;
	PossessedCharacter= nullptr;
}
