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
    virtual void EntrarState(AInterfaceEnemigo* Nave) override;
    virtual void ActualizarState(AInterfaceEnemigo* Nave, float DeltaTime) override;
    virtual void SalirState(AInterfaceEnemigo* Nave) override;

};
