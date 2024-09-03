// Fill out your copyright notice in the Description page of Project Settings.


#include "World/BaseDestructible.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Chaos/ChaosSolverActor.h"

// Sets default values
ABaseDestructible::ABaseDestructible()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateOptionalDefaultSubobject<UGeometryCollectionComponent>(TEXT("Mesh"));
	
	IsBroken = false;

	Mesh->SetNotifyBreaks(true);
	Mesh->SetEnableGravity(true);
	Mesh->SetSimulatePhysics(true);


}

// Called when the game starts or when spawned
void ABaseDestructible::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ABaseDestructible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseDestructible::Break(FVector HitPoint, FVector ImpulseDir, float Impulse)
{

	
		IsBroken = true;
		Mesh->AddImpulseAtLocation(ImpulseDir * Impulse, GetActorLocation());
	
}

