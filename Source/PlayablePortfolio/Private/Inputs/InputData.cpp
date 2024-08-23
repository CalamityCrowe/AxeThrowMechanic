// Fill out your copyright notice in the Description page of Project Settings.


#include "Inputs/InputData.h"
#include "Components/InputComponent.h"
#include "InputMappingContext.h"

UInputData::UInputData()
{
	for (size_t i = 0; i < 3; ++i)
	{
		Contexts.Add(nullptr);
		MovementActions.Add(nullptr);
		AttackActions.Add(nullptr);
		MiscActions.Add(nullptr);
	}
}
