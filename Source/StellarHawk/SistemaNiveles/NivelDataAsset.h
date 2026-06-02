// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NivelDataAsset.generated.h"

class USoundBase;
class UCreadorFactory;

UCLASS()
class STELLARHAWK_API UNivelDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
    // --- INFORMACIÓN GENERAL ---

    UPROPERTY()
    FString NombreNivel;


    // --- SISTEMA DE GENERACIÓN (FACTORY METHOD) ---

    /** * Diccionario que mapea un ID de texto con la clase Factory específica.
     * Ejemplo -> Clave: "Basico" | Valor: BP_EnemigoBasicoFactory (o tu clase C++)
     * El LevelManager instanciará solo las fábricas incluidas en esta lista.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawners")
    TMap<FName, TSubclassOf<UCreadorFactory>> FactoryClases;


    // --- ESTÉTICA Y AUDIO ---

    /** Música de fondo para el nivel */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
    USoundBase* BackgroundMusic;

    /*
    // --- BALANCE Y JUGABILIDAD ---

    //Multiplicador de dificultad global (afecta la vida o daño de los enemigos generados) 
    UPROPERTY()
    float DifficultyMultiplier = 1.0f;
	*/
};
