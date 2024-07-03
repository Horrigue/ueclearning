// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"

bool UMyUserWidget::Initialize()
{
	if(!Super::Initialize())
	{
		return false;
	}

	ButtonStart ->OnClicked.AddDynamic(this, &UMyUserWidget::Start);
	ButtonQuit ->OnClicked.AddDynamic(this, &UMyUserWidget::Quit);
	return true;
}

void UMyUserWidget::Start()
{
	// do something
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("WidgetStart"));
	UpdateHealth();
}

void UMyUserWidget::Quit()
{
	// do something
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("WidgetQuit"));
}

void UMyUserWidget::UpdateHealth()
{
	if(CurrentHealth <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("Death!"));
	} else
	{
		CurrentHealth -= 50;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("MyCurrentHealthIs%f."), CurrentHealth));
	}
}
