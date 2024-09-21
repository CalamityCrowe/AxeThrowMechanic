// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseEntity.h"
#include "AxeThrowEntity.generated.h"

/**
 * 
 */
class UInputComponent;
class UFloorCheckComponent;
class UBaseStatsComponent;
class ABaseThrowable; 


UCLASS()
class PLAYABLEPORTFOLIO_API AAxeThrowEntity : public ABaseEntity
{
	GENERATED_BODY()
public:
	AAxeThrowEntity();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void CatchMontage();
	UFUNCTION(BlueprintImplementableEvent)
	void ShakeCamera();

protected: 
	UFUNCTION(BlueprintImplementableEvent)
	void LerpCamera(); 
	UFUNCTION(BlueprintCallable)
	void LerpCameraAlpha(float Alpha);
	UFUNCTION(BlueprintImplementableEvent)
	void EquipAnim(); 
private: 
	UFUNCTION()
	void Aim();
	UFUNCTION()
	void ReleaseAim();
	UFUNCTION()
	void ThrowAxe();

	UFUNCTION(BlueprintCallable)
	void Catch(); 


	UFUNCTION()
	void Recall(); 
	UFUNCTION()
	void Equip(); 

	virtual void SetupActions(UInputComponent* PlayerInputComponent) override; 

private:
	UPROPERTY(BlueprintReadOnly, Category = "Axe Stats", meta = (AllowPrivateAccess = true))
	bool isAiming;
	UPROPERTY(BlueprintReadWrite, Category = "Axe Stats", meta = (AllowPrivateAccess = true))
	bool isThrowing;
	UPROPERTY(BlueprintReadWrite, Category = "Axe Stats", meta = (AllowPrivateAccess = true))
	bool isEquipped; 

	TObjectPtr<UBaseStatsComponent> PlayerStats;
	TObjectPtr<UFloorCheckComponent> FloorCheckComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
	float IdleLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
	float AimLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
	FVector IdleVec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
	FVector AimVec;

	FVector desiredSocketOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = true))
	TObjectPtr<ABaseThrowable> Pickaxe;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = true))
	TSubclassOf<ABaseThrowable> PickaxeRef;

	
	
};
