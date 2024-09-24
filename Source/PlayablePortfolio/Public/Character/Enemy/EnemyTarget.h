// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseEntity.h"
#include "EnemyTarget.generated.h"

/**
 * 
 */
class UWidgetComponent;
class UBaseStatsComponent;
UCLASS()
class PLAYABLEPORTFOLIO_API AEnemyTarget : public ABaseEntity
{
	GENERATED_BODY()
public:
	AEnemyTarget();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void StartWidgetRotation();
	void StopWidgetRotation();

	UBaseStatsComponent* GetHealthComponent() { return HealthComponent; }

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = true))
	TObjectPtr<UWidgetComponent> HealthBar;

	FTimerHandle PointWidgetTimer;

	void RotateWidget();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBaseStatsComponent> HealthComponent;
};
