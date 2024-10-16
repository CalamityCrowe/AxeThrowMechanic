
#include "Components/BaseStatsComponent.h"


// Sets default values for this component's properties
UBaseStatsComponent::UBaseStatsComponent() : Health(100.f), MaxHealth(100.f), bIsAlive(true)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseStatsComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UBaseStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UBaseStatsComponent::DamageHealth(float DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0)
	{
		Health = 0;
		return (bIsAlive = false);
		// Call the death function
	}
	return false; // Not dead
}


