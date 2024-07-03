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
	// ʹ��������ת����Ӱ�쵽��ɫ��ֻӰ���������ת��
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	// �ý�ɫ�泯���ٶȵķ���
	GetCharacterMovement() ->bOrientRotationToMovement = true;
	// ʹ��pawn����ת
	MySpringArm ->bUsePawnControlRotation = true;

}
 
// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// ע����ǿ������ϵͳ
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if(PlayerController)
	{
		// ʵ������ǿ������ϵͳ
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController ->GetLocalPlayer());
		if(Subsystem)
		{
			Subsystem ->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	// ͨ�������������ȥ����pitch�ӽ�
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

	// ������ǿ����
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

