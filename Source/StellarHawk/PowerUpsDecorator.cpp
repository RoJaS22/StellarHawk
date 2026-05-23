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
        // Me salto a mí mismo en la cadena devolviendo la capa de abajo
        return StatsEnvueltas;
    }

    // 2. No soy yo. Le paso la orden a la capa de abajo (si existe)
    if (StatsEnvueltas)
    {
        StatsEnvueltas = StatsEnvueltas->RemoverStat(StatARemover);
    }

    // 3. Sigo devolviéndome a mí mismo para mantener intacta esta parte de la cadena
    return this;
}
