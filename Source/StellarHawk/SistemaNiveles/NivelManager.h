// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NivelEventTrigger.h"
#include "NivelManager.generated.h"

class UCreadorFactory;
class UNivelDataAsset;

UCLASS()
class STELLARHAWK_API ANivelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANivelManager();

	void ProcessWaveTrigger(const TArray<FEnemigoSpawnRequest>& EnemiesToSpawn, FVector TriggerLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
    // --- REFERENCIAS A SISTEMAS ---

    /** Referencia instanciada de tu Factory Method en el mapa */
    UPROPERTY()
    UCreadorFactory* EnemigoFactory;
private:
    UPROPERTY()
    UNivelDataAsset* LevelData;

    UPROPERTY()
    bool bIsBossLevel;

    UPROPERTY()
    TMap<FName, UCreadorFactory*> FactoriasInstanciadas;
};
