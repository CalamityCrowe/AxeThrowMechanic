// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UBUIUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PLAYABLEPORTFOLIO_API UBUIUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override; 
	
	virtual TSharedRef<SWidget> RebuildWidget() override;


};
