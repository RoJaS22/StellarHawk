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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, Category = "Configuración del Nivel")
	UNivelDataAsset* DatosDelNivel;

	void ManejarActivacionTrigger(FName TriggerID, const TArray<FTransform>& PuntosDeSpawn);

};
