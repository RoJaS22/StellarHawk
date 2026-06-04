// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EstrategiaEnemigo.h"
#include "EstrategiaRegeneracionJefe.generated.h"

UCLASS()
class STELLARHAWK_API UEstrategiaRegeneracionJefe : public UEstrategiaEnemigo
{
	GENERATED_BODY()

public:

	UEstrategiaRegeneracionJefe();

	virtual void EjecutarEstrategia(AInterfaceEnemigo* Nave, float DeltaTime) override;

private:

	bool bYaSeRegenero;
	float PorcentajeRegeneracion;
};
