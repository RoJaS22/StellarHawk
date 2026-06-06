// Copyright Epic Games, Inc. All Rights Reserved.

#include "StellarHawkGameMode.h"
#include "StellarHawkPawn.h"
#include "SpawnerEnemigos.h"
#include "EnemigoBaseFactory.h"
#include "NaveTanque.h"

AStellarHawkGameMode::AStellarHawkGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AStellarHawkPawn::StaticClass();
}

void AStellarHawkGameMode::BeginPlay()
{
    /*
    // --- GENERAR UN SPAWNER DE CAZAS ---
    FVector PosicionCazas(1500.0f, 500.0f, 200.0f);

    // Generamos el actor Spawner vacío
    ASpawnerEnemigos* SpawnerCazas = GetWorld()->SpawnActor<ASpawnerEnemigos>(ASpawnerEnemigos::StaticClass(), PosicionCazas, FRotator::ZeroRotator);

    if (SpawnerCazas)
    {
        // ¡Aquí le asignamos el tipo de fábrica puramente en C++!
        SpawnerCazas->IniciarSpawner(UEnemigoBaseFactory::StaticClass());
    }
    */

	FVector Ubi(1500.0f, 500.0f, 200.0f);
	//AInterfaceEnemigo* Enemigo = GetWorld()->SpawnActor<AInterfaceEnemigo>(ANaveTanque::StaticClass(), Ubi, FRotator::ZeroRotator);
}

