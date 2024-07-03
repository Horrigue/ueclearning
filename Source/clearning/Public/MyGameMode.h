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
	// ��Ϸ���п�ʼִ��BeginPlay()
	virtual void BeginPlay() override;
	// ��Ϸ���е�ÿһ֡����ִ��Tick()
	virtual void Tick(float DeltaTime) override;
	// ��Ϸ�˳���ж�عؿ�ʱִ��EndPlay()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// ��������
	bool varBool;
	int32 varInt32;
	int64 varInt64;
	BYTE varByte;
	FString varString; // ������std string
	FName varName; // �����ִ�Сд �ȽϹ�ϣֵ����fname
	FText varText; // ��ʾ����ҿ�������Ϣ���ͱ��ػ�
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
