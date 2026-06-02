// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InterfaceEnemigo.h"
#include "NaveEnemiga.generated.h"

class UStaticMeshComponent;
class UEnemigoState;

UCLASS()
class STELLARHAWK_API ANaveEnemiga : public AInterfaceEnemigo
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANaveEnemiga();

    UPROPERTY()
    TArray<FVector> PuntosRuta;

    int32 IndicePuntosRutaActual = 0;

	UPROPERTY()
	TSubclassOf<AActor> Proyectil;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Atacar(float DeltaTime) override;
	virtual void Patrullar(float DeltaTime) override;

	float TiempoDesdeUltimoDisparo = 0.0f;

};
