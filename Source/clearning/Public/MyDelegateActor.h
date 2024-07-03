// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyDelegateActor.generated.h"


// 单播代理
DECLARE_DELEGATE(NoParamDelegate)
DECLARE_DELEGATE_OneParam(OneParamDelegate, FString)
DECLARE_DELEGATE_TwoParams(TwoParamDelegate, FString, int32)
DECLARE_DELEGATE_ThreeParams(ThreeParamDelegate, FString, int32, float)
DECLARE_DELEGATE_RetVal(FString, RevalDelegate)
// 多播代理
DECLARE_MULTICAST_DELEGATE_OneParam(OneParamMultiDelegate, FString)
// 动态多播代理，区别在于可以暴露给蓝图，在蓝图中进行时间的绑定
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDynamicMultiDelegate, FString, param);

UCLASS()
class CLEARNING_API AMyDelegateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyDelegateActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 单播代理
	NoParamDelegate NoParamDelegate;
	OneParamDelegate OneParamDelegate;
	TwoParamDelegate TwoParamDelegate;
	ThreeParamDelegate ThreeParamDelegate;
	RevalDelegate RevalDelegate;

	void NoParamFunction();
	void OneParamFunction(FString Str);
	void TwoParamFunction(FString Str, int32 Value);
	void ThreeParamFunction(FString Str, int32 Value, float Value1);
	FString RevalParamFunction();

	// 多播代理
	OneParamMultiDelegate OneParamMultiDelegate;

	UFUNCTION()
	void MultiDelegateFunc1(FString str);
	UFUNCTION()
	void MultiDelegateFunc2(FString str);
	UFUNCTION()
	void MultiDelegateFunc3(FString str);

	// 动态多播代理
	UPROPERTY(BlueprintAssignable)
	FDynamicMultiDelegate DynamicMultiDelegate;

	
};
