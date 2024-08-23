// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BaseStatsComponent.h"
#include "ManaStatsComponent.generated.h"

/**
 * 
 */
UCLASS()
class PLAYABLEPORTFOLIO_API UManaStatsComponent : public UBaseStatsComponent
{
	GENERATED_BODY()
public: 
	UManaStatsComponent();
protected: 
	virtual void BeginPlay() override;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	bool ConsumeMana(float ManaAmount);
	float GetManaPercentage() { return Mana / MaxMana; }
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float Mana;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	float MaxMana;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = true))
	bool bCanRegen; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = true, EditCondition = bCanRegen, EditConditionHides))
	float RegenRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Stats", meta = (AllowPrivateAccess = true, EditCondition = bCanRegen, EditConditionHides))
	float RegenTarget; 
	float Timer; 
	
};
