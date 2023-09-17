// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatCharacterBase.h"
#include "GameFramework/Character.h"
#include "Global/CombatGlobals_Common.h"
#include "InputActionValue.h"
#include "CombatPlayerCharacter.generated.h"

/**
 * Player character class
 */
UCLASS()
class COMBAT_API ACombatPlayerCharacter : public ACombatCharacterBase
{
	GENERATED_BODY()
public:
	ACombatPlayerCharacter();
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(Category = "LockTarget")
	FORCEINLINE TWeakObjectPtr<AActor> GetCurrentLockTarget() const { return CurrentLockTarget; }

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/** Bind  */
	void BindASCInput();

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void OnAbilityInputPressed(const ECombatInputID InputID);
	void OnAbilityInputReleased(const ECombatInputID InputID);

	UFUNCTION(Blueprintcallable, Category = "LockTarget")
	void SetCameraRotationToLockTarget();

	UFUNCTION(Blueprintcallable, Category = "LockTarget")
	void FindLockTarget();

	UFUNCTION(Blueprintcallable, Category = "LockTarget")
	void TryLockTarget();

	UFUNCTION(Category = "LockTarget")
	void DoLockTarget();

	UFUNCTION(Category = "LockTarget")
	void CancelLockTarget();

public:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

protected:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "EnhancedInput")
	TObjectPtr<class UCombatInputComponent> CombatInputComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	TObjectPtr<class UCombatInputConfig> InputConfig;

	UPROPERTY(EditDefaultsOnly, Category = "EnhancedInput")
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "LockTarget")
	float LockSphereRadius;

	UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category = "LockTarget")
	TWeakObjectPtr<AActor> CurrentLockTarget;

private:
	bool bIsLockingTarget;
};
