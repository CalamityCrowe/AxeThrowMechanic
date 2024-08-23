// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseEntity.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Inputs/InputData.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
// Sets default values
ABaseEntity::ABaseEntity()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateOptionalDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->TargetArmLength = 300.0f;

	Camera = CreateOptionalDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ABaseEntity::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABaseEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	BindMappingContexts(PlayerInputComponent);
	SetupActions(PlayerInputComponent);
}

void ABaseEntity::Move(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();
	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), Input.Y);
		AddMovementInput(GetActorRightVector(), Input.X);
	}
}

void ABaseEntity::RotateCamera(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(Input.X);
		AddControllerPitchInput(Input.Y);
	}
}

void ABaseEntity::BindMappingContexts(UInputComponent* PlayerInputComponent)
{
	if (PlayerInputComponent)
	{
		if (APlayerController* PC = Cast<APlayerController>(Controller))
		{
			if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
			{
				if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
				{
					InputSystem->ClearAllMappings(); // Clear all mappings
					// Loop through all contexts
					for (int i = 0; i < Inputs->Contexts.Num(); ++i)
					{
						InputSystem->AddMappingContext(Inputs->Contexts[i], 0); // Add the context to the input systey
					}
				}
			}

		}
	}
}

void ABaseEntity::SetupActions(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		PEI->BindAction(Inputs->MovementActions[0], ETriggerEvent::Triggered, this, &ABaseEntity::Move);
		PEI->BindAction(Inputs->MovementActions[1], ETriggerEvent::Triggered, this, &ABaseEntity::RotateCamera);
		PEI->BindAction(Inputs->MovementActions[2], ETriggerEvent::Started, this, &ABaseEntity::Jump);
	}
}

