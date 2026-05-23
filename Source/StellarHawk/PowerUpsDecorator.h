// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveDecorator.h"
#include "PowerUpsDecorator.generated.h"

/**
 * 
 */
UCLASS()
class STELLARHAWK_API UPowerUpsDecorator : public UNaveDecorator
{
	GENERATED_BODY()

protected:
    // UPROPERTY protege a las mejoras apiladas de ser borradas por el Garbage Collector
    UPROPERTY()
    UNaveDecorator* StatsEnvueltas;

public:
    // Función para envolver la estadística anterior
    void InicializarDecorator(UNaveDecorator* Stats)
    {
        StatsEnvueltas = Stats;
    }

    // Por defecto, devolvemos lo que sea que diga la capa anterior
    virtual float GetVelocidadMovimiento() const override
    {
        return StatsEnvueltas ? StatsEnvueltas->GetVelocidadMovimiento() : 0.0f;
    }

    virtual float GetCadenciaDisparo() const override
    {
        return StatsEnvueltas ? StatsEnvueltas->GetCadenciaDisparo() : 0.0f;
    }

    virtual bool TieneEscudo() const override
    {
        return StatsEnvueltas ? StatsEnvueltas->TieneEscudo() : false;
    }
	
};
