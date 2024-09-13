// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "BUIUWButton.generated.h"

/**
 * 
 */

UENUM(Blueprintable)

enum class EButtonType: uint8
{
	Start UMETA(DisplayName = "Start Button"), 
	Menu UMETA(DisplayName = "Menu Button"),
	Exit UMETA(DisplayName = "Exit Button")
};

UCLASS()
class PLAYABLEPORTFOLIO_API UBUIUWButton : public UButton
{
	GENERATED_BODY()
	
protected:

	TSharedRef<SWidget> RebuildWidget() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Button|Type of button", meta = (AllowPrivateAccess = true))
	EButtonType ButtonType; 

private:
	virtual FReply OnClickedAction();
	virtual void OnPressedAction();
	virtual void OnReleasedAction();
	virtual void OnHoveredAction();
	virtual void OnUnhoveredAction();
};
