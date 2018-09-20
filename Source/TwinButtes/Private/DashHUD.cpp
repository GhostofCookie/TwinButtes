// Fill out your copyright notice in the Description page of Project Settings.

#include "DashHUD.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "ConstructorHelpers.h"

ADashHUD::ADashHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> Widget(TEXT("/Game/Blueprints/BP_MainHUD"));
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), Widget.Class);
}


