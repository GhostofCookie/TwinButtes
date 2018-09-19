// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCharacter.h"
#include "CloudGameInstance.h"
#include "Engine/World.h"
#include "DashCharacterMovementComponent.h"


// Sets default values
ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UDashCharacterMovementComponent>(ACharacter::CharacterMovementComponentName)),
	CurrentJumpCount{ 0 }, MaxJumpCount{ 2 }, CurrentDashCount{ 0 }, MaxDashCount{ 2 },
	DoubleJumpZVelocity{750.f}, DashForwardVelocity{1000.f},
	Health{ 100.f }, MaxHealth{ 100.f }, bIsDead{ false }
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, BaseEyeHeight));
	CameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckHealth();
	

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ABaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABaseCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABaseCharacter::StopJump);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ABaseCharacter::Dash);
}

void ABaseCharacter::Landed(const FHitResult & Hit)
{
	CurrentJumpCount = 0;
	CurrentDashCount = 0;
}

void ABaseCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ABaseCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ABaseCharacter::StartJump()
{
	bPressedJump = true;
	if (CurrentJumpCount && CurrentJumpCount < MaxJumpCount)
		LaunchCharacter(FVector(0.f, 0.f, DoubleJumpZVelocity), false, true);
	CurrentJumpCount++;
}

void ABaseCharacter::StopJump()
{
	bPressedJump = false;

}

void ABaseCharacter::Dash()
{
	if (CurrentDashCount && CurrentDashCount < MaxDashCount)
	{
		LaunchCharacter(GetActorForwardVector() * DashForwardVelocity, true, true);
	}
	CurrentDashCount++;

}

void ABaseCharacter::AffectHealth(float Delta)
{
	Health -= Delta;
	CheckHealth();
}

void ABaseCharacter::CheckHealth()
{
	if (Health <= 0.f && !bIsDead)
	{
		bIsDead = true;

		// Restart the level to change up the cloud configuration. This isn't proper practice.
		// Cast<UCloudGameInstance>(GetGameInstance())->RestartGame();
	}
	if (Health > MaxHealth)
		Health = MaxHealth;

}

