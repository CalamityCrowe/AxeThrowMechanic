// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UBUIUserWidget.h"
#include "Components/Button.h"

void UBUIUserWidget::NativeConstruct()
{
	Super::NativeConstruct(); 
}

TSharedRef<SWidget> UBUIUserWidget::RebuildWidget()
{
	auto Result = Super::RebuildWidget();
	
	return Result;
}





