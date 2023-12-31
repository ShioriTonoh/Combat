// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/TargetActor/CombatGameplayAbilityTargetActor.h"
#include "Game/Character/CombatAICharacter.h"
#include "GAS/Ability/CombatGameplayAbility_TryTarget.h"
#include "Kismet/GameplayStatics.h"

ACombatGameplayAbilityTargetActor::ACombatGameplayAbilityTargetActor()
	: bPersitentDrawDebugShape(false)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACombatGameplayAbilityTargetActor::BeginPlay()
{
	Super::BeginPlay();

	TargetOverlapActors.Empty();
}

void ACombatGameplayAbilityTargetActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ConfirmTargetingAndContinue();
	Super::EndPlay(EndPlayReason);
}

void ACombatGameplayAbilityTargetActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (LocalTargetActorParam.TargetActorClass == GetClass())
	{
		DoSweepCheck(0, TargetHitResults, DeltaSeconds);
	}
}

void ACombatGameplayAbilityTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);

	SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();

	if (LocalTargetActorParam.MaxLifeTime > 0.f)
	{
		SetLifeSpan(LocalTargetActorParam.MaxLifeTime);
	}

	if (SourceCharacter = Cast<ACombatCharacterBase>(SourceActor))
	{
		AttachToComponent(SourceCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SourceCharacter->WeaponSocket_Combat);
	}

}

void ACombatGameplayAbilityTargetActor::StartTargetingWithNewParam(UGameplayAbility* Ability, const FCombatTargetActorParam& InParam)
{
	StartTargeting(Ability);

	LocalTargetActorParam = InParam;
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
	FQuat OverlapQuat = FQuat::Identity;
	if (IsValid(SourceCharacter))
	{
		OverlapQuat = SourceCharacter->GetMesh()->GetSocketQuaternion(SourceCharacter->WeaponSocket_Combat);
	}

	//OverlapPos.Z += 50.f;

	FCollisionShape OverlapShape;
	switch (LocalTargetActorParam.CollisionShapeInfo.CollisionShapeType)
	{
	case ECombatCollisionShape::Box:
		OverlapShape = FCollisionShape::MakeBox(LocalTargetActorParam.CollisionShapeInfo.Extent * GetActorScale());
		if (bDebug)
		{
			DrawDebugBox(GetWorld(), OverlapPos, LocalTargetActorParam.CollisionShapeInfo.Extent * GetActorScale(), OverlapQuat, FColor::Green, bPersitentDrawDebugShape, DeltaTime, 0, 1);
		}
		break;

	case ECombatCollisionShape::Capsule:
		OverlapShape = FCollisionShape::MakeCapsule(LocalTargetActorParam.CollisionShapeInfo.Radius * FMath::Max(GetActorScale().X, GetActorScale().Y), LocalTargetActorParam.CollisionShapeInfo.HalfHeight * GetActorScale().Z);
		if (bDebug)
		{
			DrawDebugCapsule(GetWorld(), OverlapPos, LocalTargetActorParam.CollisionShapeInfo.Radius * FMath::Max(GetActorScale().X, GetActorScale().Y), LocalTargetActorParam.CollisionShapeInfo.HalfHeight * GetActorScale().Z, OverlapQuat, FColor::Green, bPersitentDrawDebugShape, DeltaTime, 0, 1);
		}
		break;

	case ECombatCollisionShape::Sphere:
		OverlapShape = FCollisionShape::MakeSphere(LocalTargetActorParam.CollisionShapeInfo.Radius * FMath::Max(GetActorScale().X, GetActorScale().Y));
		if (bDebug)
		{
			DrawDebugSphere(GetWorld(), OverlapPos, LocalTargetActorParam.CollisionShapeInfo.Radius * FMath::Max(GetActorScale().X, GetActorScale().Y), 8, FColor::Green, bPersitentDrawDebugShape, DeltaTime, 0, 1);
		}
		break;

	default:
		break;
	}

	GetWorld()->OverlapMultiByChannel(OverlapResults, OverlapPos, OverlapQuat, ECollisionChannel::ECC_Pawn, OverlapShape, QueryParams);

	for (const FOverlapResult& OverlapResult : OverlapResults)
	{
		if (ACombatCharacterBase* Victim = Cast<ACombatCharacterBase>(OverlapResult.GetActor()))
		{
			if (!TargetOverlapActors.Contains(Victim))
			{
				TargetOverlapActors.AddUnique(Victim);
				ConfirmTargetingAndContinue();
				UE_LOG(LogTemp, Log, TEXT("Overlapping pawn: %s"), *Victim->GetName());
			}

		}
	}
}
