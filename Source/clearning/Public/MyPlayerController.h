// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CLEARNING_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// ∞Û∂®∞¥º¸ ‰»Î
	virtual void SetupInputComponent();
	void WheelUpFunction();
	void WheelDownFunction();

	// UserWidget
	virtual void BeginPlay() override;
	
};
