// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BUIUWButton.h"


#include "Binding/States/WidgetStateBitfield.h"
#include "Binding/States/WidgetStateRegistration.h"
#include "Widgets/SNullWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Input/SButton.h"
#include "Components/ButtonSlot.h"
#include "Styling/DefaultStyleCache.h"
#include "Styling/UMGCoreStyle.h"
#include "Blueprint/WidgetTree.h"
TSharedRef<SWidget> UBUIUWButton::RebuildWidget()
{
	MyButton = SNew(SButton)
		.OnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, OnClickedAction))
		.OnPressed(BIND_UOBJECT_DELEGATE(FSimpleDelegate, OnPressedAction))
		.OnReleased(BIND_UOBJECT_DELEGATE(FSimpleDelegate, OnReleasedAction))
		.OnHovered_UObject(this, &ThisClass::OnHoveredAction)
		.OnUnhovered_UObject(this, &ThisClass::OnUnhoveredAction)
		.ButtonStyle(&WidgetStyle)
		.ClickMethod(ClickMethod)
		.TouchMethod(TouchMethod)
		.PressMethod(PressMethod)
		.IsFocusable(IsFocusable);

	if (GetChildrenCount() > 0)
	{
		Cast<UButtonSlot>(GetContentSlot())->BuildSlot(MyButton.ToSharedRef());
	}
	return MyButton.ToSharedRef();

}

FReply UBUIUWButton::OnClickedAction()
{
	OnClicked.Broadcast(); 


	return FReply::Handled();
}

void UBUIUWButton::OnPressedAction()
{
	OnPressed.Broadcast();

}

void UBUIUWButton::OnReleasedAction()
{
	OnReleased.Broadcast();
}

void UBUIUWButton::OnHoveredAction()
{
	OnHovered.Broadcast();
}

void UBUIUWButton::OnUnhoveredAction()
{
	OnUnhovered.Broadcast();
}


