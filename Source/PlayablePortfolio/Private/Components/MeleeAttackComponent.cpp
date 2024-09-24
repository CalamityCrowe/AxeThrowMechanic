// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MeleeAttackComponent.h"
#include "Weapons/BaseThrowable.h"
#include "Character/AxeThrow/AxeThrowEntity.h"
#include "Kismet/KismetSystemLibrary.h"
#include <Character/Enemy/EnemyTarget.h>
#include "Components/BaseStatsComponent.h"

// Sets default values for this component's properties
UMeleeAttackComponent::UMeleeAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMeleeAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	if(ThrowableReference = Cast<ABaseThrowable>(GetOwner()))
	{

	}	
}


// Called every frame
void UMeleeAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMeleeAttackComponent::HitDetect()
{
	FVector start = ThrowableReference->GetActorLocation();
	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	objectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(ThrowableReference->GetPlayerRef());
	TArray<FHitResult> hits;
	UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), start, start, 5, objectTypes, false, actorsToIgnore, EDrawDebugTrace::ForDuration, hits, true);
	if(hits.Num() > 0)
	{
		for (FHitResult hit : hits)
		{
			if (AEnemyTarget* enemy = Cast<AEnemyTarget>(hit.GetActor())) 
			{
				enemy->GetHealthComponent()->DamageHealth(10);
			}
		}
	}
}



