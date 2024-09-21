// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseGun.h"

// Sets default values
ABaseGun::ABaseGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseGun::Shoot()
{
	//switch(GunState)
	//{
	//case EGunStates::Single:
	//	SingleShot();
	//	break;
	//case EGunStates::Burst:
	//	BurstShot();
	//	break;
	//case EGunStates::Auto:

	//	break;
	//}
}



bool ABaseGun::LineTraceShot(FVector Start, FVector End, FHitResult& Result)
{
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(GetOwner());
	TraceParams.AddIgnoredActor(this);
	FCollisionResponseParams ResponseParam;
	return GetWorld()->LineTraceSingleByChannel(Result, Start, End, ECollisionChannel::ECC_Visibility, TraceParams, ResponseParam);
}

