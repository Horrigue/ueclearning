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

	// 输出日志 类别名称、记录级别、打印内容
	UE_LOG(LogTemp, Error, TEXT("xxx is ok"));
	UE_LOG(LogTemp, Warning, TEXT("xxx is ok"));
	UE_LOG(LogTemp, Display, TEXT("xxx is ok"));
	// 打印到屏幕上 默认值、5.0是时间、颜色、打印内容
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("xxx is ok"));

	// fstring fname ftext三者转化
	FString MyString = TEXT("I am String");
	FName MyName = FName(*MyString);
	FText MyText = FText::FromString(MyString);
	FText text1 = FText::FromName(MyName);
	MyString = MyName.ToString();
	MyString = MyText.ToString();
	// t转n只能间接转

	// 数组TArray
	MyArray.Add(10); MyArray.Add(20); 
	MyArray.AddUnique(10); MyArray.AddUnique(40);// 添加唯一
	PrintArray();
	MyArray.Remove(20);// 值
	MyArray.RemoveAt(0);// 索引
	MyArray.RemoveSingle(10);// 第一个匹配的元素
	MyArray.Empty();
	MyArray.Reset();// 把所有元素变为0
	MyArray.Insert(60, 0); int32& temp = MyArray[0]; temp = 50;
	MyArray.Contains(10);// 是否包含
	MyArray.Find(10);// 正向是否第一个匹配元素
	MyArray.FindLast(10);// 逆向查找第一个匹配元素

	// 键值对TMap
	MyMap.Emplace(0, 1); MyMap.Emplace(6, 6); MyMap.Emplace(1, 10);// insert
	PrintMap();
	MyMap.Remove(0);// 删除key值为0的值
	MyMap.Empty();
	MyMap.Contains(10);// 找key
	MyMap.Find(10);// 找key，返回指针
	MyMap.FindKey(2);// 通过value找key，返回指针
	TArray<int32> testkeys, testvalues;// 找全部键值对
	MyMap.GenerateKeyArray(testkeys);
	MyMap.GenerateValueArray(testvalues);

	// 集合TSet
	MySet.Add(TEXT("Banana")); MySet.Add(TEXT("Apple"));
	MySet.Emplace(TEXT("Orange"));// emplace更好，可以消除临时文件
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


 