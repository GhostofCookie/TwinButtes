// Fill out your copyright notice in the Description page of Project Settings.

#include "CloudGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
//#include "Blueprint/UserWidget.h"
#include "InstructionsWidget.h"
#include "ConstructorHelpers.h"

UCloudGameInstance::UCloudGameInstance() : bWidgetLoaded{ false }
{
	static ConstructorHelpers::FClassFinder<UUserWidget> Widget(TEXT("/Game/Blueprints/BP_Instructions"));
	CurrentWidget = CreateWidget<UInstructionsWidget>(GetWorld(), Widget.Class);
	
}

void UCloudGameInstance::RestartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Testing_Platform", true);
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
