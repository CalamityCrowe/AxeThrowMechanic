// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloorCheckComponent.generated.h"


UENUM(Blueprintable)
enum class EFloorType : uint8
{
	Normal UMETA(DisplayName = "Normal Floor"),
	Slippery UMETA(DisplayName = "Slippery Floor"),
	Sticky UMETA(DisplayName = "Sticky Floor"),
	Air UMETA(DisplayName = "Air")
};

class ABaseEntity;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLAYABLEPORTFOLIO_API UFloorCheckComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFloorCheckComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TObjectPtr<ABaseEntity> PlayerRef; 

	FTimerHandle TimerHandle;

	bool LineTrace(FHitResult& HitResult, const FVector& Start, const FVector& End, ECollisionChannel CollisionChannel) const;

	void CheckFloorType();

};

UCLASS()
class PLAYABLEPORTFOLIO_API ABaseFloor : public AActor
{
	GENERATED_BODY()
public:
	ABaseFloor(); 
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	EFloorType GetFloorType() const { return FloorType; }
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Floor Type", meta = (AllowPrivateAccess = true))
	EFloorType FloorType;
};
