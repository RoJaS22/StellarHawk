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
    UNaveDecorator* StatsEnvueltas = nullptr;

public:
    // Función para envolver la estadística anterior
    void InicializarDecorator(UNaveDecorator* Stats);
    
    // Por defecto, devolvemos lo que sea que diga la capa anterior
    virtual float GetVelocidadMovimiento() const override;

    virtual float GetCadenciaDisparo() const override;
    
    virtual bool TieneEscudo() const override;
    
    virtual UNaveDecorator* RemoverStat(UClass* StatARemover) override;
	
};
