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

USTRUCT(BlueprintType)
struct FConfiguracionEntorno
{
    GENERATED_BODY()

    // La clase del asteroide puramente en C++ (tu clase que hereda de AActor)
    UPROPERTY(EditAnywhere, Category = "Entorno")
    TSubclassOf<AActor> ClaseObstaculo;

    // Cuántos queremos esparcir por el mapa
    UPROPERTY(EditAnywhere, Category = "Entorno")
    int32 Cantidad = 50;

    // FVector2D es perfecto para guardar un rango: X = Mínimo, Y = Máximo
    UPROPERTY(EditAnywhere, Category = "Entorno")
    FVector2D LimitesEjeX = FVector2D(-5000.0f, 5000.0f);

    UPROPERTY(EditAnywhere, Category = "Entorno")
    FVector2D LimitesEjeY = FVector2D(-5000.0f, 5000.0f);

    // Opcional: Variación de tamaño para que no todos los asteroides sean idénticos
    UPROPERTY(EditAnywhere, Category = "Entorno")
    FVector2D RangoDeEscala = FVector2D(1.0f, 5.0f);
};

UCLASS(BlueprintType)
class STELLARHAWK_API UNivelDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    // Tu mapa de enemigos actual
    UPROPERTY(EditAnywhere, Category = "Configuración de Oleadas")
    TMap<FName, FTriggerSpawnData> DatosDeOleadas;

    // 2. NUEVO: La configuración inicial del mapa
    UPROPERTY(EditAnywhere, Category = "Configuración del Entorno")
    FConfiguracionEntorno DatosDeAsteroides;
};
