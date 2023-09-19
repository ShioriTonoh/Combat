// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "Combat.h"
#include "CombatGlobals_Common.generated.h"

/**
 * Ability Input ID
 */
UENUM(BlueprintType)
enum class ECombatInputID : uint8
{
	None			UMETA(DisplayName = "None"),
	Move			UMETA(DisplayName = "Move"),
	Look			UMETA(DisplayName = "Look"),
	Jump			UMETA(DisplayName = "Jump"),
	Dash			UMETA(DisplayName = "Dash"),
	Lock			UMETA(DisplayName = "Lock"),
	LightAttack		UMETA(DisplayName = "LightAttack"),
	HeavyAttack		UMETA(DisplayName = "HeavyAttack"),
	Avoid			UMETA(DisplayName = "Avoid"),
	GuardPoint		UMETA(DisplayName = "GuardPoint")
};

UENUM(BlueprintType)
enum class ECombatCollisionShape : uint8
{
	None,
	Box,
	Sphere,
	Capsule
};

USTRUCT(BlueprintType, meta = (ScriptName = "CollisionShapeSturct"))
struct FCombatCollisionShape
{
	GENERATED_BODY()
	
	FCombatCollisionShape()
	: Length(0.f)
	, Extent(0.f, 0.f, 0.f)
	, Radius(0.f)
	, HalfHeight(0.f)
	, CollisionShapeType(ECombatCollisionShape::None)
	{

	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "CollisionShapeType == ECombatCollisionShape::Line", EditConditionHides))
	float Length;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "CollisionShapeType == ECombatCollisionShape::Box", EditConditionHides))
	FVector Extent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "CollisionShapeType == ECombatCollisionShape::Capsule || CollisionShapeType == ECombatCollisionShape::Sphere", EditConditionHides))
	float Radius;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(EditCondition = "CollisionShapeType == ECombatCollisionShape::Capsule", EditConditionHides))
	float HalfHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECombatCollisionShape CollisionShapeType;
};


USTRUCT(Blueprintable)
struct FCombatTargetActorParam
{
	GENERATED_USTRUCT_BODY()

public:
	FCombatTargetActorParam()
		: TaskInstanceName("TargetActor")
		, MaxLifeTime(-1.f)
	{

	}
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class ACombatGameplayAbilityTargetActor> TargetActorClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName TaskInstanceName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MaxLifeTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FCombatCollisionShape CollisionShapeInfo;

	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//FGameplayTagContainer AdditionalTagToTarget;
};

USTRUCT()
struct FCombatGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_USTRUCT_BODY()

	FCombatGameplayEffectContext()
	{

	}

	FCombatGameplayEffectContext(const FCombatGameplayEffectContext& Other)
	{
		TargetActorParam = Other.TargetActorParam;
	}

	FCombatTargetActorParam TargetActorParam;

};

/**
 * 
 */
UCLASS()
class COMBAT_API UCombatGlobals_Ability : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	
};
