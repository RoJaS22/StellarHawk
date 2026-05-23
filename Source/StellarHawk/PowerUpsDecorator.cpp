// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpsDecorator.h"

void UPowerUpsDecorator::InicializarDecorator(UNaveDecorator* Stats)
{
    StatsEnvueltas = Stats;
}

float UPowerUpsDecorator::GetVelocidadMovimiento() const
{
    return StatsEnvueltas ? StatsEnvueltas->GetVelocidadMovimiento() : 0.0f;
}

float UPowerUpsDecorator::GetCadenciaDisparo() const
{
    return StatsEnvueltas ? StatsEnvueltas->GetCadenciaDisparo() : 0.0f;
}

bool UPowerUpsDecorator::TieneEscudo() const
{
    return StatsEnvueltas ? StatsEnvueltas->TieneEscudo() : false;
}

UNaveDecorator* UPowerUpsDecorator::RemoverStat(UClass* StatARemover) 
{
    if (this->GetClass() == StatARemover)
    {
        return StatsEnvueltas;
    }

    if (StatsEnvueltas)
    {
        StatsEnvueltas = StatsEnvueltas->RemoverStat(StatARemover);
    }

    return this;
}
