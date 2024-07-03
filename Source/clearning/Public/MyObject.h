// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h"

USTRUCT(BlueprintType)
struct FMyDataTableStruct {
	GENERATED_USTRUCT_BODY()

	FMyDataTableStruct();

	UPROPERTY()
	float Health;
	UPROPERTY();
	FString Name;
	UPROPERTY()
	int32 Level;
};
/**
 * 
 */
UCLASS()
class CLEARNING_API UMyObject : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FMyDataTableStruct MyDataTableStruct;
		
	
};
