// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CombatCharacterBase.generated.h"

/**
 * Character base class, including basic funtion for player and AI
 */

UCLASS()
class COMBAT_API ACombatCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Returns Gameplay ability system component
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool GenerateWeapon();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void UpdateWeaponPosition(bool bUseCombatSocket = false);

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Abilities")
	TObjectPtr<class UCombatAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<AActor> WeaponClass;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName WeaponSocket_Idle;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName WeaponSocket_Combat;

	UPROPERTY(Transient)
	TObjectPtr<AActor> WeaponInstance;
};
