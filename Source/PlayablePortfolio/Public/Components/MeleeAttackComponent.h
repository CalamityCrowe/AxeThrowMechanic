// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MeleeAttackComponent.generated.h"

class ABaseThrowable;
class AAxeThrowEntity;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAYABLEPORTFOLIO_API UMeleeAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMeleeAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void HitDetect();

private:

	UPROPERTY(EditdefaultsOnly, BlueprintReadOnly, Category = "Reference", meta = (AllowPrivateAccess = true))
	TObjectPtr<ABaseThrowable> ThrowableReference;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "bools", meta = (AllowPrivateAccess = true))
	bool bIsAttacking = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Count", meta = (AllowPrivateAccess = true))
	int AttackCount = 0;

	UPROPERTY(EditdefaultsOnly, BlueprintReadOnly, Category = "Montages", meta = (AllowPrivateAccess = true))
	TArray<UAnimMontage*> AttackMontages;


};
