// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DashSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TWINBUTTES_API UDashSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FTransform CheckpointTransform;
	
	UDashSaveGame();
	
	
};
