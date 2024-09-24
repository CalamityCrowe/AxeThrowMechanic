// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/EnemyTarget.h"
#include "Gameframework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include <Components/BaseStatsComponent.h>
AEnemyTarget::AEnemyTarget()
{
	PrimaryActorTick.bCanEverTick = true;
	GetSpringArm()->DestroyComponent();
	GetCamera()->DestroyComponent();

	HealthComponent = CreateDefaultSubobject<UBaseStatsComponent>(TEXT("Health Component"));

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar"));
	HealthBar->SetupAttachment(GetMesh());
	HealthBar->SetRelativeLocation(FVector(0, 0, 100));
	HealthBar->SetDrawSize(FVector2D(100, 20));
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

void AEnemyTarget::StartWidgetRotation()
{
	HealthBar->SetVisibility(true);
	GetWorldTimerManager().SetTimer(PointWidgetTimer, this, &AEnemyTarget::RotateWidget, 0.01f, true);
}

void AEnemyTarget::StopWidgetRotation()
{
	HealthBar->SetVisibility(false);
	GetWorldTimerManager().ClearTimer(PointWidgetTimer);
}

void AEnemyTarget::RotateWidget()
{
	FVector PlayerLoc = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation(); // Player Location
	FVector WidgetLoc = HealthBar->GetComponentLocation(); // Widget Location

	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(WidgetLoc, PlayerLoc); // Look at player

	FRotator newRot = UKismetMathLibrary::RInterpTo(HealthBar->GetComponentRotation(), LookAtRot, GetWorld()->GetDeltaSeconds(), 5.0f); // Rotate widget to player

	HealthBar->SetWorldRotation(FRotator(0,newRot.Yaw,0)); // Set new rotation
}
