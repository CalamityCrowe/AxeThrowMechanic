// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGun.generated.h"

UENUM(Blueprintable)
enum class EGunStates : uint8
{
	Single UMETA(DisplayName = "Single"),
	Burst UMETA(DisplayName = "Burst"),
	Auto UMETA(DisplayName = "Auto"),
	Charge UMETA(DisplayName = "Charge"),
	Projectile UMETA(DisplayName = "Projectile"),
};

UCLASS()
class PLAYABLEPORTFOLIO_API ABaseGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Shoot();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Type", meta = (AllowPrivateAccess = true))
	EGunStates GunState;



	bool LineTraceShot(FVector Start, FVector End, FHitResult& Result);

};
