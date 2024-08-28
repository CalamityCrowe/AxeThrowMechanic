// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseLevelSwitch.generated.h"

class UCapsuleComponent;
class UNiagaraComponent;

UCLASS()
class PLAYABLEPORTFOLIO_API ABaseLevelSwitch : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseLevelSwitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Level", meta = (AllowPrivateAccess = true))
	TSoftObjectPtr<UWorld> LevelToLoad;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Particle", meta = (AllowPrivateAccess = true))
	TObjectPtr<UNiagaraComponent> ParticleSystem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Collider", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCapsuleComponent> Collider;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
