// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DashHUD.generated.h"

/**
 * 
 */
UCLASS()
class TWINBUTTES_API ADashHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ADashHUD();

protected:
	UPROPERTY()
	class UUserWidget* CurrentWidget;

	bool bWidgetLoaded;


	
	
	
};
