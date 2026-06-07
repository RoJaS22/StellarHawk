// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STELLARHAWK_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    AMainMenuPlayerController();    

public:
    // La clase del Widget de tu menú principal (tu WBP_MainMenu)
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<class UUserWidget> MainMenuWidgetClass;

protected:
    virtual void BeginPlay() override;
	
};
