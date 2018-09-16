// Fill out your copyright notice in the Description page of Project Settings.

#include "CloudDashGameMode.h"
#include "BaseCharacter.h"

ACloudDashGameMode::ACloudDashGameMode()
{
	DefaultPawnClass = ABaseCharacter::StaticClass();
}
