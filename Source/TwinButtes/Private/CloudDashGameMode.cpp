// Fill out your copyright notice in the Description page of Project Settings.

#include "CloudDashGameMode.h"
#include "BaseCharacter.h"
#include "DashController.h"
#include "DashHUD.h"

ACloudDashGameMode::ACloudDashGameMode()
{
	DefaultPawnClass = ABaseCharacter::StaticClass();
	PlayerControllerClass = ADashController::StaticClass();
	HUDClass = ADashHUD::StaticClass();


}

void ACloudDashGameMode::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACloudDashGameMode::Tick(float Delta)
{

}

