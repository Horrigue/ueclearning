// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "MyPawn.h"
#include "Blueprint/UserWidget.h"

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("WheelUp", IE_Pressed, this, &AMyPlayerController::WheelUpFunction);
	InputComponent->BindAction("WheelDown", IE_Pressed, this, &AMyPlayerController::WheelDownFunction);

}

void AMyPlayerController::WheelUpFunction()
{
	if (GetPawn()) {
		AMyPawn* MyCameraPawn = Cast<AMyPawn>(GetPawn());
		if (MyCameraPawn) {
			MyCameraPawn->Zoom(1, 10);
		}
	}
}

void AMyPlayerController::WheelDownFunction()
{
	if (GetPawn()) {
		AMyPawn* MyCameraPawn = Cast<AMyPawn>(GetPawn());
		if (MyCameraPawn) {
			MyCameraPawn->Zoom(0, 10);
		}
	}
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UClass* WidgetClass = LoadClass<UUserWidget>(NULL,TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BPs/UMG_Widget.UMG_Widget_C'"));
	UUserWidget* MyWidgetClass = nullptr;
	MyWidgetClass = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	MyWidgetClass ->AddToViewport();
}
