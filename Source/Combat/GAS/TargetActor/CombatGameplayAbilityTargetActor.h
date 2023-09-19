// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "Global/CombatGlobals_Common.h"
#include "CombatGameplayAbilityTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class COMBAT_API ACombatGameplayAbilityTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:
	ACombatGameplayAbilityTargetActor();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;

	/** Initialize and begin targeting logic  */
	virtual void StartTargeting(UGameplayAbility* Ability) override;

	void StartTargetingWithNewParam(UGameplayAbility* Ability, const FCombatTargetActorParam& InParam);

	/** Requesting targeting data, but not necessarily stopping/destroying the task. Useful for external target data requests. */
	virtual void ConfirmTargetingAndContinue() override;

	FGameplayAbilityTargetDataHandle MakeTargetData(const TArray<FHitResult>& HitResults) const;

	FORCEINLINE const FCombatTargetActorParam& GetTargetActorParam() const { return *&LocalTargetActorParam; }

protected:
	virtual void DoSweepCheck(int32 Steps, TArray<FHitResult>& HitResults, float DeltaTime);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Targeting")
	TArray<FHitResult> TargetHitResults;

	UPROPERTY(/*BlueprintReadOnly, Category = "Targeting"*/)
	TArray<TWeakObjectPtr<AActor>> TargetOverlapActors;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Targeting")
	FCombatTargetActorParam LocalTargetActorParam;

};
