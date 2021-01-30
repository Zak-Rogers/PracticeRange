// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuGameMode.h"

void AMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
	ChangeMenuWidget(startWidget);
}

void AMenuGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> newWidget)
{
	if (currentWidget != nullptr)
	{
		currentWidget->RemoveFromViewport();
		currentWidget = nullptr;
	}
	if (newWidget != nullptr)
	{
		currentWidget = CreateWidget<UUserWidget>(GetWorld(), newWidget);
		if (currentWidget != nullptr)
		{
			currentWidget->AddToViewport();
		}
	}
}
