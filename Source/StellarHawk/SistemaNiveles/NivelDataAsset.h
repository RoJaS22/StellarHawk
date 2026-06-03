// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CreadorFactory.h"
#include "NivelDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FEnemySpawnInfo
{
    GENERATED_BODY()

    // Qué fábrica usaremos para este enemigo específico
    UPROPERTY(EditAnywhere, Category = "Config de Spawn")
    TSubclassOf<UCreadorFactory> ClaseDeFabrica;

    UPROPERTY(EditAnywhere, Category = "Config de Spawn")
    int32 Cantidad = 1;

    UPROPERTY(EditAnywhere, Category = "Config de Spawn")
    float DelayEntreSpawn = 0.5f;
};

//Estructura que agrupa todos los enemigos que se activarán al mismo tiempo
USTRUCT(BlueprintType)
struct FTriggerSpawnData
{
    GENERATED_BODY()

    // Esto permite que un solo trigger genere, por ejemplo: 3 cazas Y 1 nave pesada a la vez.
    UPROPERTY(EditAnywhere, Category = "Config de Spawn")
    TArray<FEnemySpawnInfo> ListaDeEnemigos;
};


UCLASS()
class STELLARHAWK_API UNivelDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Configuración del Nivel")
    TMap<FName, FTriggerSpawnData> DatosDeOleadas;

};
