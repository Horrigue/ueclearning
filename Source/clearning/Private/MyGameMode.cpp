// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"

AMyGameMode::AMyGameMode() {
	DefaultPawnClass = AMyPawn::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	HUDClass = AMyHUD::StaticClass();
	GameStateClass = AMyGameState::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	// �����־ ������ơ���¼���𡢴�ӡ����
	UE_LOG(LogTemp, Error, TEXT("xxx is ok"));
	UE_LOG(LogTemp, Warning, TEXT("xxx is ok"));
	UE_LOG(LogTemp, Display, TEXT("xxx is ok"));
	// ��ӡ����Ļ�� Ĭ��ֵ��5.0��ʱ�䡢��ɫ����ӡ����
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("xxx is ok"));

	// fstring fname ftext����ת��
	FString MyString = TEXT("I am String");
	FName MyName = FName(*MyString);
	FText MyText = FText::FromString(MyString);
	FText text1 = FText::FromName(MyName);
	MyString = MyName.ToString();
	MyString = MyText.ToString();
	// tתnֻ�ܼ��ת

	// ����TArray
	MyArray.Add(10); MyArray.Add(20); 
	MyArray.AddUnique(10); MyArray.AddUnique(40);// ���Ψһ
	PrintArray();
	MyArray.Remove(20);// ֵ
	MyArray.RemoveAt(0);// ����
	MyArray.RemoveSingle(10);// ��һ��ƥ���Ԫ��
	MyArray.Empty();
	MyArray.Reset();// ������Ԫ�ر�Ϊ0
	MyArray.Insert(60, 0); int32& temp = MyArray[0]; temp = 50;
	MyArray.Contains(10);// �Ƿ����
	MyArray.Find(10);// �����Ƿ��һ��ƥ��Ԫ��
	MyArray.FindLast(10);// ������ҵ�һ��ƥ��Ԫ��

	// ��ֵ��TMap
	MyMap.Emplace(0, 1); MyMap.Emplace(6, 6); MyMap.Emplace(1, 10);// insert
	PrintMap();
	MyMap.Remove(0);// ɾ��keyֵΪ0��ֵ
	MyMap.Empty();
	MyMap.Contains(10);// ��key
	MyMap.Find(10);// ��key������ָ��
	MyMap.FindKey(2);// ͨ��value��key������ָ��
	TArray<int32> testkeys, testvalues;// ��ȫ����ֵ��
	MyMap.GenerateKeyArray(testkeys);
	MyMap.GenerateValueArray(testvalues);

	// ����TSet
	MySet.Add(TEXT("Banana")); MySet.Add(TEXT("Apple"));
	MySet.Emplace(TEXT("Orange"));// emplace���ã�����������ʱ�ļ�
	PrintSet();
}

void AMyGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMyGameMode::PrintArray()
{
	for (auto i = MyArray.CreateConstIterator(); i; i++) {
		UE_LOG(LogTemp, Warning, TEXT("%d"), *i);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%d"), *i));
	}
}

void AMyGameMode::PrintMap()
{
	for (auto& testmap : MyMap) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("key:%d""value:%d"), testmap.Key, testmap.Value));
	}
}

void AMyGameMode::PrintSet()
{
	for (auto& testset : MySet) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("%s"), *testset));
	}
}


 