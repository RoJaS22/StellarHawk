// Fill out your copyright notice in the Description page of Project Settings.


#include "CreadorFactory.h"
#include "InterfaceEnemigo.h"

AInterfaceEnemigo* UCreadorFactory::SpawnearEnemigo(UWorld* Mundo, FTransform SpawnTransformacion, int32 NivelEnemigo)
{
    AInterfaceEnemigo* NuevoEnemigo = CrearEnemigo(Mundo, SpawnTransformacion);

    /*
    if (NuevoEnemigo)
    {
        NuevoEnemigo->InicializarStats(NivelEnemigo);
    }
    */

    return NuevoEnemigo;
}
