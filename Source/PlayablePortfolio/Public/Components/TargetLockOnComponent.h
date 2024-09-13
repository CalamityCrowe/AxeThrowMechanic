// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetLockOnComponent.generated.h"

class ABaseEntity;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAYABLEPORTFOLIO_API UTargetLockOnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTargetLockOnComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void TriggerTargetLockOn();


	void TargetLockOn();
	void StopTargetLockOn();
	UFUNCTION(BlueprintCallable)
	void SwitchTarget(float AxisValue);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LockOn", meta = (AllowPrivateAccess = true))
	float LockOnRadius; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LockOn", meta = (AllowPrivateAccess = true))
	TSubclassOf<AActor> TargetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LockOn", meta = (AllowPrivateAccess = true))
	TObjectPtr<AActor> CurrentTarget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LockOn", meta = (AllowPrivateAccess = true))
	float LockOnScale;

	TObjectPtr<ABaseEntity> PlayerRef;

	FTimerHandle LockOnTimerHandle;

	bool bIsLockedOn;



private:
	UFUNCTION(BlueprintCallable)
	TArray<AActor*> TraceForTargets(); 

	AActor* GetClosestTarget(const TArray<AActor*>& Targets);

	float CloseToCentre(AActor*); 

	FRotator GetLockOnCameraRotation(AActor* Target);


};
