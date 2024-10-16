
#include "Components/DamageComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UDamageComponent::GetDamage()
{
	float FinalDamage = GetRandomDamage();
	return FinalDamage;
}

float UDamageComponent::GetRandomDamage()
{
	return UKismetMathLibrary::RandomFloatInRange(MinRandomDamage, MaxRandomDamage);
}


