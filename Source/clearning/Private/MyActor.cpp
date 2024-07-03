// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ����Ĭ��ֵ
	MyScene = CreateDefaultSubobject<USceneComponent>(TEXT("MyCustomScene"));
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyCustomMesh"));
	MyParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyCustomParticle"));
	MyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyCustomBox"));
	MyAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("MyCustomAudio"));

	// ������
	RootComponent = MyScene;
	MyMesh->SetupAttachment(MyScene);
	MyParticle->SetupAttachment(MyScene);
	MyBox->SetupAttachment(MyScene);
	MyAudio->SetupAttachment(MyBox);

	// ��̬������Դ��text�ڵ�·������ͨ���Ҽ���Ʒ������Դ���ã�FObjectFinder
	static ConstructorHelpers::FObjectFinder<UStaticMesh>TempStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	MyMesh->SetStaticMesh(TempStaticMesh.Object);
	static ConstructorHelpers::FObjectFinder<UParticleSystem>TempParticleSystem(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	MyParticle->SetTemplate(TempParticleSystem.Object);
	static ConstructorHelpers::FObjectFinder<USoundWave>TempSound(TEXT("/Script/Engine.SoundCue'/Game/StarterContent/Audio/Collapse_Cue.Collapse_Cue'"));
	MyAudio->SetSound(TempSound.Object);

	// ��̬������FClassFinder
	static ConstructorHelpers::FClassFinder<AActor> TempMyActor(TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_CeilingLight.Blueprint_CeilingLight_C'"));
	MyActor = TempMyActor.Class;

	// ��ײ����
	MyBox ->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// ��ײ��������
	MyBox ->SetCollisionObjectType(ECC_WorldDynamic);
	// ��ײ��Ӧ
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
	
	// ��̬������Դ LoadObject
	UStaticMesh* MyTempStaticMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (MyTempStaticMesh) {
		MyMesh->SetStaticMesh(MyTempStaticMesh);
	}
	// ��̬������ LoadClass ע��ҲҪ�ڽ�β��_C
	UClass* MyTempClass = LoadClass<AActor>(this, TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_CeilingLight.Blueprint_CeilingLight_C'"));
	if (MyTempClass) {
		AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(MyTempClass, FVector::ZeroVector, FRotator::ZeroRotator);
	}

	// �ص�����ײ
	MyBox ->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::BeginOverlapFunction);
	MyBox ->OnComponentEndOverlap.AddDynamic(this, &AMyActor::EndOverlapFunction);
	MyBox ->OnComponentHit.AddDynamic(this, &AMyActor::HitFunction);

	// ����box��С
	MyBox ->SetBoxExtent(FVector(64, 64, 64));

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector MyOffset = FVector(1, 0, 0);
	FHitResult HitResult;
	// ��ƫ�������Ƿ������ײ��������ײ����
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

