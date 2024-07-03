// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 创建默认值
	MyScene = CreateDefaultSubobject<USceneComponent>(TEXT("MyCustomScene"));
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyCustomMesh"));
	MyParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyCustomParticle"));
	MyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyCustomBox"));
	MyAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("MyCustomAudio"));

	// 创建绑定
	RootComponent = MyScene;
	MyMesh->SetupAttachment(MyScene);
	MyParticle->SetupAttachment(MyScene);
	MyBox->SetupAttachment(MyScene);
	MyAudio->SetupAttachment(MyBox);

	// 静态加载资源（text内的路径可以通过右键物品复制资源引用）FObjectFinder
	static ConstructorHelpers::FObjectFinder<UStaticMesh>TempStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	MyMesh->SetStaticMesh(TempStaticMesh.Object);
	static ConstructorHelpers::FObjectFinder<UParticleSystem>TempParticleSystem(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	MyParticle->SetTemplate(TempParticleSystem.Object);
	static ConstructorHelpers::FObjectFinder<USoundWave>TempSound(TEXT("/Script/Engine.SoundCue'/Game/StarterContent/Audio/Collapse_Cue.Collapse_Cue'"));
	MyAudio->SetSound(TempSound.Object);

	// 静态加载类FClassFinder
	static ConstructorHelpers::FClassFinder<AActor> TempMyActor(TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_CeilingLight.Blueprint_CeilingLight_C'"));
	MyActor = TempMyActor.Class;

	// 碰撞设置
	MyBox ->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// 碰撞对象类型
	MyBox ->SetCollisionObjectType(ECC_WorldDynamic);
	// 碰撞响应
	MyBox ->SetCollisionResponseToAllChannels(ECR_Overlap);
	
	
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	if(MyParticle)
	{
		MyParticle ->Deactivate();
	}
	
	// 动态加载资源 LoadObject
	UStaticMesh* MyTempStaticMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (MyTempStaticMesh) {
		MyMesh->SetStaticMesh(MyTempStaticMesh);
	}
	// 动态加载类 LoadClass 注意也要在结尾加_C
	UClass* MyTempClass = LoadClass<AActor>(this, TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_CeilingLight.Blueprint_CeilingLight_C'"));
	if (MyTempClass) {
		AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(MyTempClass, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	// 重叠与碰撞
	MyBox ->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::BeginOverlapFunction);
	MyBox ->OnComponentEndOverlap.AddDynamic(this, &AMyActor::EndOverlapFunction);
	MyBox ->OnComponentHit.AddDynamic(this, &AMyActor::HitFunction);

	// 设置box大小
	MyBox ->SetBoxExtent(FVector(64, 64, 64));

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector MyOffset = FVector(1, 0, 0);
	FHitResult HitResult;
	// ：偏移量，是否产生碰撞，返回碰撞参数
	AddActorLocalOffset(MyOffset, false, &HitResult);
	AddActorWorldOffset(MyOffset, false, &HitResult);

}

void AMyActor::BeginOverlapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// do something
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("BeginOverlapSuccess")));
	MyParticle ->Activate();
}

void AMyActor::EndOverlapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// do something
	MyParticle ->Deactivate();
}

void AMyActor::HitFunction(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// do something
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("HitSuccess")));
}

