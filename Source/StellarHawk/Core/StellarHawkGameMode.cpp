// Copyright Epic Games, Inc. All Rights Reserved.

#include "StellarHawkGameMode.h"
#include "StellarHawkPawn.h"
#include "MainMenuPlayerController.h"

AStellarHawkGameMode::AStellarHawkGameMode()
{
    PlayerControllerClass = AMainMenuPlayerController::StaticClass();
}

void AStellarHawkGameMode::BeginPlay()
{
}

UClass* AStellarHawkGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    FString MapName = GetWorld()->GetMapName();

    // Unreal suele añadir un prefijo a las cadenas de mapas en tiempo de ejecución, por eso usamos Contains
    if (MapName.Contains("MapaMenu"))
    {
        // Si estamos en el mapa del menú, devolvemos nullptr para que NO se genere ninguna nave
        return nullptr;
    }

    // Si estamos en cualquier otro mapa de combate, devolvemos la clase de tu nave
    return AStellarHawkPawn::StaticClass();
}

