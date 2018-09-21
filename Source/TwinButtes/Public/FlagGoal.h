// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlagGoal.generated.h"

UCLASS()
class TWINBUTTES_API AFlagGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlagGoal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class USphereComponent* CollisionSphere;

	UFUNCTION()
	void PlantFlag();

	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
