// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/EnemyTarget.h"
#include "Gameframework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
AEnemyTarget::AEnemyTarget()
{
	PrimaryActorTick.bCanEverTick = true;
	GetSpringArm()->DestroyComponent();
	GetCamera()->DestroyComponent();
}

void AEnemyTarget::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemyTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyTarget::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
