// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../EstrategiaEnemigo.h"
#include "EstrategiaExplosionTanque.generated.h"

UCLASS()
class STELLARHAWK_API UEstrategiaExplosionTanque : public UEstrategiaEnemigo
{
	GENERATED_BODY()

public:

	UEstrategiaExplosionTanque();

	virtual void EjecutarEstrategia(AInterfaceEnemigo* Nave, float DeltaTime) override;

private:

	bool bExplosionActivada;

	float TiempoExplosion;
	float TiempoEntreExplosiones;
};
