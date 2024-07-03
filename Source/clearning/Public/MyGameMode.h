// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "MyPawn.h"
#include "MyHUD.h"
#include "MyPlayerController.h"
#include "MyGameState.h"
#include "MyPlayerState.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CLEARNING_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
	AMyGameMode();

public:
	// 游戏运行开始执行BeginPlay()
	virtual void BeginPlay() override;
	// 游戏运行的每一帧都在执行Tick()
	virtual void Tick(float DeltaTime) override;
	// 游戏退出或卸载关卡时执行EndPlay()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// 声明类型
	bool varBool;
	int32 varInt32;
	int64 varInt64;
	BYTE varByte;
	FString varString; // 类似于std string
	FName varName; // 不区分大小写 比较哈希值查找fname
	FText varText; // 显示（玩家看到的信息）和本地化
	FVector varVector; // x axis, y axis, z axis
	FRotator varRotator; // x Roll, y Pitch, z Yaw
	FTransform varTransform; // conbine of fvector frotator scale

	TArray<int32> MyArray;
	void PrintArray();

	TMap<int32, int32> MyMap;
	void PrintMap();

	TSet<FString> MySet;
	void PrintSet();
};
