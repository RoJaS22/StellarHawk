// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InterfaceEnemigo.h"
#include "NaveTanque.generated.h"

class UStaticMeshComponent;
class UEnemigoState;

UCLASS()
class STELLARHAWK_API ANaveTanque : public AInterfaceEnemigo
{
	GENERATED_BODY()

public:
	ANaveTanque();

	int32 IndicePuntosRutaActual = 0;

	UPROPERTY()
		TSubclassOf<AActor> Proyectil;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Atacar(float DeltaTime) override;
	virtual void Patrullar(float DeltaTime) override;

	float TiempoDesdeUltimoDisparo = 0.0f;
};