// Fill out your copyright notice in the Description page of Project Settings.


#include "Level/BaseLevelSwitch.h"
#include "Components/CapsuleComponent.h"
#include "NiagaraComponent.h"
#include "Character/BaseEntity.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ABaseLevelSwitch::ABaseLevelSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateOptionalDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	RootComponent = Collider;
	ParticleSystem = CreateOptionalDefaultSubobject<UNiagaraComponent>(TEXT("ParticleSystem"));
	ParticleSystem->SetupAttachment(RootComponent);

	Collider->OnComponentBeginOverlap.AddDynamic(this, &ABaseLevelSwitch::OnOverlapBegin); 

}

// Called when the game starts or when spawned
void ABaseLevelSwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseLevelSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseLevelSwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Emerald, "Collided"); 

	if(ABaseEntity* player = Cast<ABaseEntity>(OtherActor))
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), LevelToLoad); 
	}
}
