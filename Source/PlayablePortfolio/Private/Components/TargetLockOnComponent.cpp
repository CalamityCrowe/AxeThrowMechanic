// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TargetLockOnComponent.h"
#include "Character/BaseEntity.h"
#include "Kismet/KismetSystemLibrary.h" // Include for tracing functions
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "Character/Enemy/EnemyTarget.h"

// Sets default values for this component's properties
UTargetLockOnComponent::UTargetLockOnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTargetLockOnComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerRef = Cast<ABaseEntity>(GetOwner());
	// ...
	LockOnRadius = 1000.0f;

}


// Called every frame
void UTargetLockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTargetLockOnComponent::TriggerTargetLockOn()
{
	if (bIsLockedOn == false)
	{
		AActor* Target = GetClosestTarget(TraceForTargets());
		if (IsValid(Target))
		{
			PlayerRef->GetController()->SetIgnoreLookInput(true);
			CurrentTarget = Target;
			Cast<AEnemyTarget>(CurrentTarget)->StartWidgetRotation();
			bIsLockedOn = true;
			GetWorld()->GetTimerManager().SetTimer(LockOnTimerHandle, this, &UTargetLockOnComponent::TargetLockOn, 0.01f, true);
		}
	}
	else
	{
		StopTargetLockOn();
	}
}

void UTargetLockOnComponent::TargetLockOn()
{
	FVector PlayerDis = PlayerRef->GetActorLocation();
	FVector TargetDis = CurrentTarget->GetActorLocation();

	if (UKismetMathLibrary::Vector_Distance(PlayerDis, TargetDis) > LockOnRadius)
	{
		StopTargetLockOn();
	}
	else
	{
		float Roll = PlayerRef->GetCamera()->GetComponentRotation().Roll;

		FRotator LookRot = GetLockOnCameraRotation(CurrentTarget);
		FRotator ContRot = PlayerRef->GetController()->GetControlRotation();
		FRotator NewRot = UKismetMathLibrary::RInterpTo(ContRot, LookRot, 0.01, 20.0f);
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, "AAAAAAAAAAAAA");
		PlayerRef->GetController()->SetControlRotation(FRotator(NewRot.Pitch, NewRot.Yaw, ContRot.Roll));
	}
}

void UTargetLockOnComponent::StopTargetLockOn()
{
	bIsLockedOn = false;
	Cast<AEnemyTarget>(CurrentTarget)->StopWidgetRotation();
	GetWorld()->GetTimerManager().ClearTimer(LockOnTimerHandle);
	PlayerRef->GetController()->SetIgnoreLookInput(false);
}

void UTargetLockOnComponent::SwitchTarget(float AxisValue)
{
	if (bIsLockedOn)
	{
		float 	localCompare = 0;

		FVector CamLoc = PlayerRef->GetCamera()->GetComponentLocation();
		TArray<AActor*> Enemies = TraceForTargets();
		FHitResult OutHit;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(PlayerRef);

		AActor* newTarget = nullptr;  // Temporary variable to store the best candidate


		float previousDot = 0; 
		for (AActor* Enemy : Enemies)
		{
			FVector EnemyLoc = Enemy->GetActorLocation();
			FVector DirectionToEnemy = (EnemyLoc - CamLoc).GetSafeNormal();  // Get normalized direction to enemy

			if (GetWorld()->LineTraceSingleByChannel(OutHit, CamLoc, EnemyLoc, ECC_Visibility, Params))
			{
				if (CurrentTarget != Enemy)
				{
					FVector CamRight = PlayerRef->GetCamera()->GetRightVector();


					float dot = UKismetMathLibrary::Dot_VectorVector(CamRight, DirectionToEnemy);
					// Check if input axis (left or right) matches the dot product sign
					if ((AxisValue > 0 && dot > 0) || (AxisValue < 0 && dot < 0))
					{
						float distanceFromCenter = CloseToCentre(Enemy);
						// Check if this enemy is closer to the center of the screen than the previous best
						if (distanceFromCenter > localCompare)
						{
							localCompare = distanceFromCenter;
							newTarget = Enemy;
						}
					}
				}
			}
		}
		if(newTarget)
		{
			Cast<AEnemyTarget>(CurrentTarget)->StopWidgetRotation();
			CurrentTarget = newTarget;
			Cast<AEnemyTarget>(CurrentTarget)->StartWidgetRotation();
		}
	}
}

TArray<AActor*> UTargetLockOnComponent::TraceForTargets()
{
	TArray<AActor*> Targets;
	TArray<AActor*> IgnoredActors;
	TArray<FHitResult> Hits;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1));


	if (UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), PlayerRef->GetActorLocation(), PlayerRef->GetActorLocation(), LockOnRadius, ObjectTypes, false, IgnoredActors, EDrawDebugTrace::None, Hits, true, FLinearColor::Red, FLinearColor::Green, 5.0f))
	{
		for (FHitResult Hit : Hits)
		{
			AActor* HitActor = Hit.GetActor();
			if (HitActor && HitActor->GetClass() == TargetClass)
			{
				Targets.Add(HitActor);
			}
		}
	}
	return Targets;
}

AActor* UTargetLockOnComponent::GetClosestTarget(const TArray<AActor*>& Targets)
{
	AActor* ClosestTarget = nullptr;
	float LocalCompareFloat = 0.0f;
	FVector Start = PlayerRef->GetCamera()->GetComponentLocation();
	for (AActor* Target : Targets)
	{
		FVector End = Target->GetActorLocation();
		FHitResult OutHit;
		if (GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility))
		{
			float Dot = CloseToCentre(Target);
			if (Dot > LocalCompareFloat)
			{
				LocalCompareFloat = Dot;
				ClosestTarget = Target;
			}
		}
	}

	return ClosestTarget;
}

float UTargetLockOnComponent::CloseToCentre(AActor* Target)
{

	FVector TargLoc = Target->GetActorLocation();
	FVector PlayerLoc = PlayerRef->GetActorLocation();

	FRotator LookRot = UKismetMathLibrary::FindLookAtRotation(PlayerLoc, TargLoc);

	return UKismetMathLibrary::Dot_VectorVector(PlayerRef->GetCamera()->GetForwardVector(), LookRot.Vector());
}

FRotator UTargetLockOnComponent::GetLockOnCameraRotation(AActor* Target)
{
	FVector CamLoc = PlayerRef->GetCamera()->GetComponentLocation();
	FVector TargLoc = Target->GetActorLocation();
	FVector PlayerDis = PlayerRef->GetActorLocation();

	float Z = TargLoc.Z - (UKismetMathLibrary::Vector_Distance(PlayerDis, TargLoc) / LockOnScale);

	FVector NewLoc = FVector(TargLoc.X, TargLoc.Y, Z);

	return UKismetMathLibrary::FindLookAtRotation(CamLoc, NewLoc);
}

