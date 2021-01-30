// Fill out your copyright notice in the Description page of Project Settings.

#include "PractiseRangeGameModeBase.h"

void APractiseRangeGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> newWidget)
{
	if (currentWidget != nullptr) // if there is a currentWidget.
	{
		currentWidget->RemoveFromViewport();
		currentWidget = nullptr;
	}
	if (newWidget != nullptr) // if a newWidget has been passed in.
	{
		currentWidget = CreateWidget<UUserWidget>(GetWorld(), newWidget); // create new widget.
		if (currentWidget != nullptr) // if sucessful add to the viewport.
		{
			currentWidget->AddToViewport();
		}
	}
}

void APractiseRangeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}
