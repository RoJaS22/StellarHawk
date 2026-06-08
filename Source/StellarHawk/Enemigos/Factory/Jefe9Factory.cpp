// Fill out your copyright notice in the Description page of Project Settings.


#include "Jefe9Factory.h"
#include "NaveJefeNivel9.h"
#include "UObject/ConstructorHelpers.h"

UJefe9Factory::UJefe9Factory()
{
	Jefe9 = ANaveJefeNivel9::StaticClass();
}

AInterfaceEnemigo* UJefe9Factory::CrearEnemigo(UWorld* Mundo, FTransform SpawnTransformacion)
{
    if (!Mundo || !Jefe9) return nullptr;

    FActorSpawnParameters SpawnParametros;
    SpawnParametros.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    return Mundo->SpawnActor<AInterfaceEnemigo>(Jefe9, SpawnTransformacion, SpawnParametros);
}
