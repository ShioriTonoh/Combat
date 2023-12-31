// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Character/CombatAICharacter.h"
#include "Game/Controller/CombatAIController.h"
#include "GAS/CombatAbilitySystemComponent.h"

ACombatAICharacter::ACombatAICharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCombatAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	check(AbilitySystemComponent);
}

void ACombatAICharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AIController = Cast<ACombatAIController>(NewController);
	if (IsValid(AIController))
	{
		AIController->SetupBehaviorTree(BehaviorTree);
		AIController->RunBehavior();
	}
}

void ACombatAICharacter::UnPossessed()
{
	Super::UnPossessed();

	AIController->StopBehavior();
	AIController = nullptr;
}
