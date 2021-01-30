// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PRACTISERANGE_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ChangeMenuWidget(TSubclassOf<UUserWidget> newWidget);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Menu Widgets")
	TSubclassOf<UUserWidget> startWidget;
	UUserWidget* currentWidget;

};
