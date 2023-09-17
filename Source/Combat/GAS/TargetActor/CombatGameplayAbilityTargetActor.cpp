// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/TargetActor/CombatGameplayAbilityTargetActor.h"
#include "Game/Character/CombatAICharacter.h"
#include "GAS/Ability/CombatGameplayAbility_TryTarget.h"
#include "Kismet/GameplayStatics.h"

ACombatGameplayAbilityTargetActor::ACombatGameplayAbilityTargetActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACombatGameplayAbilityTargetActor::BeginPlay()
{
	Super::BeginPlay();

	TargetOverlapActors.Empty();

	switch (TargetActorParam.CollisionShapeInfo.CollisionShapeType)
	{
		//TODO: Spawn collision component from trigger event payload
	case ECombatCollisionShape::Box:
	default:
		break;
	}
}

void ACombatGameplayAbilityTargetActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ConfirmTargetingAndContinue();
}

void ACombatGameplayAbilityTargetActor::Tick(float DeltaSeconds)
{
	DoSweepCheck(0, TargetHitResults, DeltaSeconds);
}

void ACombatGameplayAbilityTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);

	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();

	if (TargetActorParam.MaxLifeTime > 0.f)
	{
		SetLifeSpan(TargetActorParam.MaxLifeTime);
	}

}

void ACombatGameplayAbilityTargetActor::ConfirmTargetingAndContinue()
{
	if (SourceActor && OwningAbility /*&& (TargetHitResults.Num() > 0)*/)
	{
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(TargetHitResults);
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}

FGameplayAbilityTargetDataHandle ACombatGameplayAbilityTargetActor::MakeTargetData(const TArray<FHitResult>& HitResults) const
{
	return StartLocation.MakeTargetDataHandleFromActors(TargetOverlapActors);
	//return StartLocation.MakeTargetDataHandleFromActors(OwningAbility, HitResults);
}

void ACombatGameplayAbilityTargetActor::DoSweepCheck(int32 Steps, TArray<FHitResult>& HitResults, float DeltaTime)
{
	TArray<FOverlapResult> OverlapResults;

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = false;
	QueryParams.bReturnPhysicalMaterial = false;

	if (SourceActor)
	{
		QueryParams.AddIgnoredActor(SourceActor);
	}

	FVector OverlapPos = GetActorLocation();
	OverlapPos.Z += 50.f;

	FCollisionShape OverlapShape = FCollisionShape::MakeBox(TargetActorParam.CollisionShapeInfo.Extent);
	if (bDebug)
	{
		DrawDebugBox(GetWorld(), OverlapPos, TargetActorParam.CollisionShapeInfo.Extent, FColor::Green, false, DeltaTime, 0, 1);
	}

	GetWorld()->OverlapMultiByChannel(OverlapResults, OverlapPos, FQuat::Identity, ECollisionChannel::ECC_Pawn, OverlapShape, QueryParams);

	for (const FOverlapResult& OverlapResult : OverlapResults)
	{
		if (ACombatAICharacter* Enemy = Cast<ACombatAICharacter>(OverlapResult.GetActor()))
		{
			if (!TargetOverlapActors.Contains(Enemy))
			{
				TargetOverlapActors.AddUnique(Enemy);
				ConfirmTargetingAndContinue();
				UE_LOG(LogTemp, Log, TEXT("Overlapping pawn: %s"), *Enemy->GetName());
			}

		}
	}
}
