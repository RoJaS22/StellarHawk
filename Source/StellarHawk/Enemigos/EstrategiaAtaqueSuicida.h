// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EstrategiaEnemigo.h"
#include "EstrategiaAtaqueSuicida.generated.h"

UCLASS()
class STELLARHAWK_API UEstrategiaAtaqueSuicida : public UEstrategiaEnemigo
{
	GENERATED_BODY()

public:

	UEstrategiaAtaqueSuicida();

	virtual void EjecutarEstrategia(AInterfaceEnemigo* Nave, float DeltaTime) override;

private:

	bool bModoSuicida;
};
