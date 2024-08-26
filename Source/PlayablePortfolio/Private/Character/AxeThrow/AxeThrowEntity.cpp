// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AxeThrow/AxeThrowEntity.h"
#include <Kismet/KismetMathLibrary.h>
#include "Components/BaseStatsComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Inputs/InputData.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "Weapons/BaseThrowable.h"

AAxeThrowEntity::AAxeThrowEntity() :IdleLength(200), AimLength(125), IdleVec(0, 20, 40), AimVec(0, 60, 50)
{
	PrimaryActorTick.bCanEverTick = true;
	PlayerStats = CreateOptionalDefaultSubobject<UBaseStatsComponent>(TEXT("Player Stats"));

	GetSpringArm()->TargetArmLength = IdleLength;
	GetSpringArm()->SocketOffset = IdleVec;
}

void AAxeThrowEntity::BeginPlay()
{
	Super::BeginPlay();
	if (PickaxeRef)
	{
		Pickaxe = GetWorld()->SpawnActor<ABaseThrowable>(PickaxeRef, GetActorLocation(), GetActorRotation());
		FAttachmentTransformRules* rules = new FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
		Pickaxe->AttachToComponent(GetMesh(), *rules, "EquipSocket");
		Pickaxe->SetPlayerRef(this);
	}
}

void AAxeThrowEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAxeThrowEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	SetupActions(PlayerInputComponent);
}

void AAxeThrowEntity::LerpCameraAlpha(float Alpha)
{
	float armLength = UKismetMathLibrary::Lerp(IdleLength, AimLength, Alpha);
	FVector cameraPos = FMath::Lerp(IdleVec, AimVec, Alpha);

	GetSpringArm()->TargetArmLength = armLength;
	desiredSocketOffset = cameraPos;
	GetSpringArm()->SocketOffset = cameraPos;
}

void AAxeThrowEntity::Aim()
{
	isAiming = true;
	GetCharacterMovement()->MaxWalkSpeed = 250.f;
	LerpCamera();
}

void AAxeThrowEntity::ReleaseAim()
{
	isAiming = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	LerpCamera();
}

void AAxeThrowEntity::ThrowAxe()
{
	if (isAiming)
	{
		if (IsValid(Pickaxe))
		{
			if (Pickaxe->GetIsThrown() == false)
			{
				isThrowing = true;
			}
		}
	}
}

void AAxeThrowEntity::Catch()
{
	if (Pickaxe)
	{
		Pickaxe->Catch(GetMesh());
	}
}

void AAxeThrowEntity::Recall()
{
	if (Pickaxe)
	{
		Pickaxe->Recall();
	}
}

void AAxeThrowEntity::SetupActions(UInputComponent* PlayerInputComponent)
{
	ABaseEntity::SetupActions(PlayerInputComponent);
	if (UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		PEI->BindAction(GetInputs()->AttackActions[0], ETriggerEvent::Started, this, &AAxeThrowEntity::Aim);
		PEI->BindAction(GetInputs()->AttackActions[0], ETriggerEvent::Completed, this, &AAxeThrowEntity::ReleaseAim);
		PEI->BindAction(GetInputs()->AttackActions[1], ETriggerEvent::Started, this, &AAxeThrowEntity::ThrowAxe);
		PEI->BindAction(GetInputs()->AttackActions[2], ETriggerEvent::Started, this, &AAxeThrowEntity::Recall);

	}
}
