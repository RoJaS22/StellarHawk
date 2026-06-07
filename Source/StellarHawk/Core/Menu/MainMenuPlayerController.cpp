// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMainMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // 1. Configurar el ratón y el modo de entrada
    bShowMouseCursor = true;

    FInputModeUIOnly InputModeData;
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    SetInputMode(InputModeData);

    // 2. Crear y mostrar el Menú Principal en la pantalla
    if (MainMenuWidgetClass)
    {
        UUserWidget* MenuWidget = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
        if (MenuWidget)
        {
            MenuWidget->AddToViewport();
        }
    }
}
