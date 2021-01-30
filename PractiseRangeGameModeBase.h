// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "PractiseRangeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PRACTISERANGE_API APractiseRangeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable) // allows function to be called in blueprints.
	void ChangeMenuWidget(TSubclassOf<UUserWidget> newWidget);
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Widgets")
	TSubclassOf<UUserWidget> newWidget;
	UUserWidget* currentWidget;
};
