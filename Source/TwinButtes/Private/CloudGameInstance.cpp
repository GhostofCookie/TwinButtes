// Fill out your copyright notice in the Description page of Project Settings.

#include "CloudGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCharacter.h"
#include "Engine/World.h"
#include "InstructionsWidget.h"
#include "ConstructorHelpers.h"
#include "DashSaveGame.h"

UCloudGameInstance::UCloudGameInstance() : bWidgetLoaded{ false }, bGameOver{ false }
{
	static ConstructorHelpers::FClassFinder<UUserWidget> Widget(TEXT("/Game/Blueprints/BP_Instructions"));
	CurrentWidget = CreateWidget<UInstructionsWidget>(GetWorld(), Widget.Class);
	
}

void UCloudGameInstance::RestartGame()
{
	//UGameplayStatics::OpenLevel(GetWorld(), "Testing_Platform", true);
}

void UCloudGameInstance::ShowInstructions()
{
	if (!bWidgetLoaded)
	{
		FStringClassReference Widget(TEXT("/Game/Blueprints/BP_Instructions.BP_Instructions_C"));
		CurrentWidget = CreateWidget<UInstructionsWidget>(GetWorld(), Widget.TryLoadClass<UInstructionsWidget>());
		if (CurrentWidget)
			CurrentWidget->AddToViewport();
		bWidgetLoaded = true;
	}
	else
	{
		if (CurrentWidget)
			CurrentWidget->RemoveFromParent();
		bWidgetLoaded = false;
	}
}

void UCloudGameInstance::SetCheckpoint(FTransform NewTransform)
{
	UDashSaveGame* SaveInst = Cast<UDashSaveGame>(UGameplayStatics::CreateSaveGameObject(UDashSaveGame::StaticClass()));
	SaveInst->CheckpointTransform = NewTransform;
	UGameplayStatics::SaveGameToSlot(SaveInst, "TB_Save_0000", 0);
	
}

void UCloudGameInstance::LoadCheckpoint()
{
	UDashSaveGame* SaveInst = Cast<UDashSaveGame>(UGameplayStatics::CreateSaveGameObject(UDashSaveGame::StaticClass()));
	SaveInst = Cast<UDashSaveGame>(UGameplayStatics::LoadGameFromSlot("TB_Save_0000", 0));

	ABaseCharacter* Player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	Player->Respawn(SaveInst->CheckpointTransform);
}
