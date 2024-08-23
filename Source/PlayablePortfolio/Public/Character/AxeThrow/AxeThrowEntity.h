// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseEntity.h"
#include "AxeThrowEntity.generated.h"

/**
 * 
 */
class UInputComponent;


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

protected: 
	UFUNCTION(BlueprintImplementableEvent)
	void LerpCamera(); 
	UFUNCTION(BlueprintCallable)
	void LerpCameraAlpha(float Alpha);
private: 
	UFUNCTION()
	void Aim();
	UFUNCTION()
	void ReleaseAim();
	UFUNCTION()
	void ThrowAxe();

	virtual void SetupActions(UInputComponent* PlayerInputComponent) override; 

private:
	UPROPERTY(BlueprintReadOnly, Category = "Axe Stats", meta = (AllowPrivateAccess = true))
	bool isAiming;
	UPROPERTY(BlueprintReadWrite, Category = "Axe Stats", meta = (AllowPrivateAccess = true))
	bool isThrowing;

	TObjectPtr<class UBaseStatsComponent> PlayerStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
	float IdleLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
	float AimLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
	FVector IdleVec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = true))
	FVector AimVec;

	FVector desiredSocketOffset;


};
