// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "Editor/EditorEngine.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MySpringArmComponent"));
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCameraComponent"));
	MySpringArm ->TargetArmLength = 400.0f;
	MyCamera ->SetupAttachment(MySpringArm);
	MySpringArm ->SetupAttachment(RootComponent);
	// 使控制器的转动不影响到角色，只影响摄像机的转动
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	// 让角色面朝加速度的方向
	GetCharacterMovement() ->bOrientRotationToMovement = true;
	// 使用pawn的旋转
	MySpringArm ->bUsePawnControlRotation = true;

}
 
// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 注册增强输入子系统
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if(PlayerController)
	{
		// 实例化增强输入子系统
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController ->GetLocalPlayer());
		if(Subsystem)
		{
			Subsystem ->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	// 通过摄像机管理器去限制pitch视角
	PlayerController ->PlayerCameraManager ->ViewPitchMax = 10.f;
	PlayerController ->PlayerCameraManager ->ViewPitchMin = -30.f;
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 设置增强输入
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent -> BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		EnhancedInputComponent -> BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		EnhancedInputComponent -> BindAction(JumpAction, ETriggerEvent::Started, this, &AMyCharacter::Jump);
		EnhancedInputComponent -> BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyCharacter::StopJumping);
	}

}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	FVector2d MovementVector = Value.Get<FVector2d>();
	if(Controller)
	{
		const FRotator Rotation = Controller ->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	FVector2d LookAxisVector = Value.Get<FVector2d>();
	if(Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

