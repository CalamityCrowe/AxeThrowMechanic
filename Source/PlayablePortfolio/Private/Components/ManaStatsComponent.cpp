// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ManaStatsComponent.h"

UManaStatsComponent::UManaStatsComponent() :Mana(100.0f), MaxMana(100.0f), bCanRegen(true), RegenRate(1.0f), RegenTarget(100.0f), Timer(0.0f)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UManaStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UManaStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bCanRegen)
	{
		if (Mana < MaxMana)
		{
			Timer += DeltaTime;
			if (Timer >= RegenRate)
			{
				Mana += 1.0f;
				Timer = 0.0f;
			}
		}
	}
}

bool UManaStatsComponent::ConsumeMana(float ManaAmount)
{
	if (ManaAmount > Mana)
	{
		return false;
	}
	else
	{
		if (bCanRegen)
		{
			Timer = 0.0f; // resets the timer
		}
		Mana -= ManaAmount;
		return true;
	}
}


