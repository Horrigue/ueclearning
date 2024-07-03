// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDelegateActor.h"

// Sets default values
AMyDelegateActor::AMyDelegateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ���������
	NoParamDelegate.BindUObject(this, &AMyDelegateActor::NoParamFunction);
	OneParamDelegate.BindUObject(this, &AMyDelegateActor::OneParamFunction);
	TwoParamDelegate.BindUObject(this, &AMyDelegateActor::TwoParamFunction);
	ThreeParamDelegate.BindUObject(this, &AMyDelegateActor::ThreeParamFunction);
	RevalDelegate.BindUObject(this, &AMyDelegateActor::RevalParamFunction);

	// �ಥ�����
	OneParamMultiDelegate.AddUObject(this, &AMyDelegateActor::MultiDelegateFunc1);
	OneParamMultiDelegate.AddUObject(this, &AMyDelegateActor::MultiDelegateFunc2);
	OneParamMultiDelegate.AddUObject(this, &AMyDelegateActor::MultiDelegateFunc3);

}

// Called when the game starts or when spawned
void AMyDelegateActor::BeginPlay()
{
	Super::BeginPlay();

	// ִ�е�������
	NoParamDelegate.ExecuteIfBound();
	FString strValue = RevalDelegate.Execute();

	// ִ�жಥ����
	OneParamMultiDelegate.Broadcast("OneParamMultiDelegate");

	// ִ�ж�̬�ಥ
	DynamicMultiDelegate.Broadcast("DynamicMultiDelegate");
	
}

// Called every frame
void AMyDelegateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyDelegateActor::NoParamFunction()
{
	// do something
}

void AMyDelegateActor::OneParamFunction(FString Str)
{
	// do something
}

void AMyDelegateActor::TwoParamFunction(FString Str, int32 Value)
{
	// do something
}

void AMyDelegateActor::ThreeParamFunction(FString Str, int32 Value, float Value1)
{
	// do something
}

FString AMyDelegateActor::RevalParamFunction()
{
	// do something
	FString str = FString::Printf(TEXT("RevalParamDelegate"));
	return str;
}

void AMyDelegateActor::MultiDelegateFunc1(FString str)
{
	FString TmpStr = str.Append("1");
}

void AMyDelegateActor::MultiDelegateFunc2(FString str)
{
	FString TmpStr = str.Append("2");
}

void AMyDelegateActor::MultiDelegateFunc3(FString str)
{
	FString TmpStr = str.Append("3");
}

