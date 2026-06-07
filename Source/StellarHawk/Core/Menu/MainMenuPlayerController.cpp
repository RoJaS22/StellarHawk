// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "Framework/Application/SlateApplication.h"

AMainMenuPlayerController::AMainMenuPlayerController()
{
    static ConstructorHelpers::FClassFinder<UUserWidget> MenuWidgetAsset(TEXT("/Game/WBP_MainMenu.WBP_MainMenu_C"));

    if (MenuWidgetAsset.Succeeded())
    {
        MainMenuWidgetClass = MenuWidgetAsset.Class;
    }
}

void AMainMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    FString MapName = GetWorld()->GetMapName();

    // Solo activamos el ratón y el Widget si realmente estamos en el mapa del menú
    if (MapName.Contains("MapaMenu"))
    {
        bShowMouseCursor = true;

        FInputModeUIOnly InputModeData;
        InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        SetInputMode(InputModeData);

        if (MainMenuWidgetClass)
        {
            UUserWidget* MenuWidget = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
            if (MenuWidget)
            {
                MenuWidget->AddToViewport();
            }
        }
    }
    else
    {
        // Si no es el mapa del menú, configuramos la entrada normal del juego
        bShowMouseCursor = false;
        bEnableClickEvents = false;
        bEnableMouseOverEvents = false;

        // 2. Forzar el modo de entrada al juego (sin consumir el clic inicial)
        FInputModeGameOnly InputModeData;
        InputModeData.SetConsumeCaptureMouseDown(false);
        SetInputMode(InputModeData);

        // 3. Enfocar la ventana gráfica a nivel de sistema
        if (FSlateApplication::IsInitialized())
        {
            FSlateApplication::Get().SetAllUserFocusToGameViewport();
        }

        if (GEngine && GEngine->GameViewport)
        {
            GEngine->GameViewport->SetMouseLockMode(EMouseLockMode::LockAlways);
            GEngine->GameViewport->SetMouseCaptureMode(EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown);
        }
    }
}
