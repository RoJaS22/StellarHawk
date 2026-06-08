// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveJefe.h"
#include "NaveJefeNivel6.generated.h"

class UCreadorFactory;

/**
 * 
 */
UCLASS()
class STELLARHAWK_API ANaveJefeNivel6 : public ANaveJefe
{
	GENERATED_BODY()

public:
	ANaveJefeNivel6();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category = "Fábrica | Spawner")
    UCreadorFactory* Fabrica;

    FTimerHandle TemporizadorInvocacion;

    UPROPERTY(EditAnywhere, Category = "Fábrica | Spawner")
    float TiempoEntreInvocaciones = 60.0f;

    UPROPERTY(EditAnywhere, Category = "Fábrica | Spawner")
    int32 CantidadAliadosPorMinuto = 1;

    UPROPERTY(EditAnywhere, Category = "Fábrica | Spawner")
    float DistanciaSeparacionSpawn = 150.0f;

    void SpawnearOleadaAliados();
	
};
