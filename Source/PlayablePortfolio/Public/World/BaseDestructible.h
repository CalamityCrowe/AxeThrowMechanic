// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseDestructible.generated.h"

class UGeometryCollectionComponent;
UCLASS()
class PLAYABLEPORTFOLIO_API ABaseDestructible : public AActor
{
	GENERATED_BODY()
	
	// Sets default values for this actor's properties
	ABaseDestructible();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
	void Break(FVector HitPoint, FVector ImpulseDir, float Impulse);
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool IsBroken; 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = true))
	TObjectPtr<UGeometryCollectionComponent> Mesh;

};
