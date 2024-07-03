// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyObject.h"
#include "MyGameInstance.h"
// �����ҡ�ۺ������������תλ������
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

// ö��
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
	// �ɼ���Ĭ�����
	UPROPERTY(VisibleDefaultsOnly)
	int VisibleDefaultsOnlyInt;
	// �ɱ༭ʵ����ϸ�����
	UPROPERTY(EditInstanceOnly)
	FString EditInstanceOnlyString;
	// 
	UPROPERTY(VisibleAnywhere)
	FVector VisibleAnywhereVector;

	// ��ͼ��ֻ��
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 BluePrintReadOnlyInt;
	// ��ͼ�ж�д
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BluePrintReadWriteInt;

	// Ŀ¼category
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyIntValue");
	int32 Value1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyIntValue|MySubIntValue");// Ŀ¼|��Ŀ¼
	int32 Value2;

	// Ԫ����˵����meta
	// DisplayName����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "MyValue3DisplayName"))
	int32 MyValue3;

	// EditCondition�������Ʊ༭(���㲼�������ſ��Ա༭)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Controller"))
	bool isController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "isController"))
	float Value3;

	// ToolTip����˵��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "IsControllerTrue"))
	bool isTrue;



	//ufunction
	// ��¶���ǵĺ�������ͼ�пɵ���
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void PrintFun1();
	// ���麯������
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MyFunction")
	bool PrintFun2();
	
	// BlueprintImplementableEvent����C++�����������ܶ�����ͼ������
	UFUNCTION(BlueprintImplementableEvent)
	void test1();// �¼�
	UFUNCTION(BlueprintImplementableEvent)
	int test2();// ����
	UFUNCTION(BlueprintImplementableEvent)
	void test11(const FString& MyString);
	UFUNCTION(BlueprintImplementableEvent)
	int test22(const FString& MyString);

	// BlueprintNativeEvent����C++����������ͼ�ڿ����ػ�����
	UFUNCTION(BlueprintNativeEvent)// ʵ��ʱҪ�ں����_Implementation
	void testa();
	UFUNCTION(BlueprintNativeEvent)
	int testb();
	UFUNCTION(BlueprintNativeEvent)
	void testc(const FString& MyString);
	UFUNCTION(BlueprintNativeEvent)
	int testd(const FString& MyString);
	// Ԫ����˵����metaͬ������ʹ��
	


	
	// uenum
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyEnum");
	TEnumAsByte<MyEnumType::MyCustomEnum> MyCustomEnum;

	// ustruct ����break
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
	// ��껬���ƶ���ͷ����
	void Zoom(bool Direction, float ZoomSpeed);




};