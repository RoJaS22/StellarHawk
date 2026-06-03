// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EstrategiaEnemigo.h"
#include "EstrategiaAtaqueRapido.generated.h"

UCLASS()
class STELLARHAWK_API UEstrategiaAtaqueRapido : public UEstrategiaEnemigo
{
	GENERATED_BODY()

public:
	UEstrategiaAtaqueRapido();

	virtual void EjecutarEstrategia(AInterfaceEnemigo* Nave, float DeltaTime) override;

private:
	float TiempoAcumulado;
	float DuracionAtaqueRapido;
	float TiempoEntreActivaciones;

	bool bAtaqueRapidoActivo;
	float VelocidadAtaqueOriginal;
};
