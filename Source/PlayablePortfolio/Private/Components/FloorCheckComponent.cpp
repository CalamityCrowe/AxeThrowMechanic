// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/FloorCheckComponent.h"
#include "Character/BaseEntity.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values for this component's properties
UFloorCheckComponent::UFloorCheckComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFloorCheckComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<ABaseEntity>(GetOwner());


	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UFloorCheckComponent::CheckFloorType, 0.2f, true);
	// ...

}


// Called every frame
void UFloorCheckComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UFloorCheckComponent::LineTrace(FHitResult& HitResult, const FVector& Start, const FVector& End, ECollisionChannel CollisionChannel) const
{

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.2f, 0, 1);

	return GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, CollisionChannel, CollisionQueryParams);
}

void UFloorCheckComponent::CheckFloorType()
{
	FHitResult HitResult;
	FVector Start = GetOwner()->GetActorLocation();
	FVector End = Start - FVector(0, 0, 100);
	if (LineTrace(HitResult, Start, End, ECC_Visibility))
	{
		if (ABaseFloor* floor = Cast<ABaseFloor>(HitResult.GetActor()))
		{
			switch (floor->GetFloorType())
			{
			case EFloorType::Normal:
				PlayerRef->GetCharacterMovement()->GroundFriction = 8.0f;
				PlayerRef->GetCharacterMovement()->BrakingDecelerationWalking = 2048;
				PlayerRef->GetCharacterMovement()->MaxAcceleration = 2048;
				break;
			case EFloorType::Slippery:
				PlayerRef->GetCharacterMovement()->GroundFriction = 0.0f;
				PlayerRef->GetCharacterMovement()->BrakingDecelerationWalking = 350;
				UE_LOG(LogTemp, Warning, TEXT("Slippery Floor"));
				break;
			case EFloorType::Sticky:
				UE_LOG(LogTemp, Warning, TEXT("Sticky Floor"));
				break;

			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Floor"));
			PlayerRef->GetCharacterMovement()->GroundFriction = 8.0f;
			PlayerRef->GetCharacterMovement()->BrakingDecelerationWalking = 2048;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Hit"));
	}
}

ABaseFloor::ABaseFloor()
{
	PrimaryActorTick.bCanEverTick = true;
	FloorType = EFloorType::Normal;
}

void ABaseFloor::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
