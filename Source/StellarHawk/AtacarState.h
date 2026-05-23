// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemigoState.h"
#include "AtacarState.generated.h"

UCLASS()
class STELLARHAWK_API UAtacarState : public UEnemigoState
{
	GENERATED_BODY()

public:
    virtual void EntrarState(ANaveEnemiga* Nave) override;
    virtual void ActualizarState(ANaveEnemiga* Nave, float DeltaTime) override;
    virtual void SalirState(ANaveEnemiga* Nave) override;

private:
    // Temporizador interno del estado para controlar la cadencia de fuego
    float TiempoDesdeUltimoDisparo;
};
