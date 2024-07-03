// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("MyRootComponent"));
	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArmComponent"));
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCameraComponent"));
	RootComponent = MyRoot;
	MySpringArm->SetupAttachment(MyRoot);
	MyCamera->SetupAttachment(MySpringArm);
	// ����Ĭ����ײΪfalse
	MySpringArm->bDoCollisionTest = false;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	FVector MyLocation = FVector(0, 0, 0);
	FRotator MyRotation = FRotator(-50, 0, 0);
	FVector MyScale = FVector(1, 1, 1);
	SetActorLocation(MyLocation);
	SetActorRotation(MyRotation);
	SetActorScale3D(MyScale);

	// �������ģ��
	TSubclassOf<UMyObject> MySubClassObject = UMyObject::StaticClass();
	// ʵ������
	MyTestObject = NewObject<UMyObject>(GetWorld(), MySubClassObject);
	// ����
	if (MyTestObject) {
		// F�������ǰҪ��*������Ĳ���
		UE_LOG(LogTemp, Warning, TEXT("MyTextObject is %s"), *MyTestObject->GetName());
		UE_LOG(LogTemp, Warning, TEXT("MyHealth is %s"), MyTestObject->MyDataTableStruct.Health);
	}

	// ʵ����
	MyInstance = Cast<UMyGameInstance>(GetWorld()->GetFirstPlayerController());;
	if (MyInstance) {
		UE_LOG(LogTemp, Warning, TEXT("MyInstance is %s"), *MyInstance->GetName());
		UE_LOG(LogTemp, Warning, TEXT("MyAPPID is %s"), *MyInstance->MyAPPID);
	}
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyPawn::PrintFun1()
{
}

bool AMyPawn::PrintFun2()
{
	return false;
}

void AMyPawn::testa_Implementation()
{
}

int AMyPawn::testb_Implementation()
{
	return 0;
}

void AMyPawn::testc_Implementation(const FString& MyString)
{
}

int AMyPawn::testd_Implementation(const FString& MyString)
{
	return 0;
}

void AMyPawn::Zoom(bool Direction, float ZoomSpeed)
{
	if (Direction) {
		if (MySpringArm->TargetArmLength >= 300 && MySpringArm->TargetArmLength < 5000) {
			MySpringArm->TargetArmLength += (ZoomSpeed * 2);
		}
	}
	else {
		if (MySpringArm->TargetArmLength < 300 && MySpringArm->TargetArmLength >= 5000) {
			MySpringArm->TargetArmLength -= (ZoomSpeed * 2);
		}
	}
}
