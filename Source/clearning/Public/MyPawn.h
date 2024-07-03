// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyObject.h"
#include "MyGameInstance.h"
// 摄像机摇臂和相机并设置旋转位移缩放
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

// 枚举
UENUM(BlueprintType)
namespace MyEnumType {
	enum MyCustomEnum {
		Type1, Type2, Type3
	};
}

USTRUCT(BlueprintType)
struct FMyTestStruct {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTestStruct")
	int32 Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTestStruct")
	FString MyName;
};


UCLASS()
class CLEARNING_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// uproperty
	// 可见类默认面板
	UPROPERTY(VisibleDefaultsOnly)
	int VisibleDefaultsOnlyInt;
	// 可编辑实例化细节面板
	UPROPERTY(EditInstanceOnly)
	FString EditInstanceOnlyString;
	// 
	UPROPERTY(VisibleAnywhere)
	FVector VisibleAnywhereVector;

	// 蓝图中只读
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 BluePrintReadOnlyInt;
	// 蓝图中读写
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BluePrintReadWriteInt;

	// 目录category
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyIntValue");
	int32 Value1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyIntValue|MySubIntValue");// 目录|子目录
	int32 Value2;

	// 元数据说明符meta
	// DisplayName别名
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "MyValue3DisplayName"))
	int32 MyValue3;

	// EditCondition条件控制编辑(满足布尔条件才可以编辑)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Controller"))
	bool isController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "isController"))
	float Value3;

	// ToolTip解释说明
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "IsControllerTrue"))
	bool isTrue;



	//ufunction
	// 暴露我们的函数在蓝图中可调用
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void PrintFun1();
	// 纯虚函数定义
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MyFunction")
	bool PrintFun2();
	
	// BlueprintImplementableEvent，在C++中声明，不能定义蓝图可重载
	UFUNCTION(BlueprintImplementableEvent)
	void test1();// 事件
	UFUNCTION(BlueprintImplementableEvent)
	int test2();// 函数
	UFUNCTION(BlueprintImplementableEvent)
	void test11(const FString& MyString);
	UFUNCTION(BlueprintImplementableEvent)
	int test22(const FString& MyString);

	// BlueprintNativeEvent，在C++中声明，蓝图内可重载或不重载
	UFUNCTION(BlueprintNativeEvent)// 实现时要在后面加_Implementation
	void testa();
	UFUNCTION(BlueprintNativeEvent)
	int testb();
	UFUNCTION(BlueprintNativeEvent)
	void testc(const FString& MyString);
	UFUNCTION(BlueprintNativeEvent)
	int testd(const FString& MyString);
	// 元数据说明符meta同样可以使用
	


	
	// uenum
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyEnum");
	TEnumAsByte<MyEnumType::MyCustomEnum> MyCustomEnum;

	// ustruct 可以break
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCustomStruct")
	FMyTestStruct MyCustomStruct;



	UPROPERTY()
	UMyObject* MyTestObject;

	UPROPERTY()
	UMyGameInstance* MyInstance;

public:
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "MySceneComponent")
	USceneComponent* MyRoot;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "MySceneComponent")
	USpringArmComponent* MySpringArm;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "MySceneComponent")
	UCameraComponent* MyCamera;
	// 鼠标滑轮移动镜头缩放
	void Zoom(bool Direction, float ZoomSpeed);




};