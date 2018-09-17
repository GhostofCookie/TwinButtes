// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "BaseCharacter.generated.h"

UCLASS()
class TWINBUTTES_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void CheckHealth();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the character is no longer in the air
	virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void StartJump();

	UFUNCTION()
	void StopJump();

	UFUNCTION()
	void Dash();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	UCapsuleComponent* CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Movement")
	float DoubleJumpZVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Movement")
	float DashForwardVelocity;

	UPROPERTY()
	UCharacterMovementComponent* MovementComponent;

	UFUNCTION()
	void AffectHealth(float Delta);

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY()
	float MaxHealth;

	UPROPERTY(BlueprintReadOnly)
	bool bIsDead;

	UPROPERTY()
	FVector StartLocation;



private:
	int CurrentJumpCount, CurrentDashCount;
	int MaxJumpCount, MaxDashCount;
	
	
};
