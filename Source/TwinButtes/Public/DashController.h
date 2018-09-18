// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DashController.generated.h"

/**
 * 
 */
UCLASS()
class TWINBUTTES_API ADashController : public APlayerController
{
	GENERATED_BODY()

	ADashController(const FObjectInitializer& ObjectInitializer);

	// Executes when a pawn is possessed.
	virtual void Possess(APawn* InPawn) override;
	
	
};
