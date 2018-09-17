// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CloudGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TWINBUTTES_API UCloudGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCloudGameInstance();

	UFUNCTION()
	void RestartGame();

	UFUNCTION()
	void ShowInstructions();

protected:
	UPROPERTY()
	class UUserWidget* CurrentWidget;

	bool bWidgetLoaded;

	
	
};
