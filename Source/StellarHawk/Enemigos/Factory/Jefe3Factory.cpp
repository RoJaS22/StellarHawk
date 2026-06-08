// Fill out your copyright notice in the Description page of Project Settings.


#include "Jefe3Factory.h"
#include "NaveJefeNivel3.h"
#include "UObject/ConstructorHelpers.h"

UJefe3Factory::UJefe3Factory()
{
	Jefe3 = ANaveJefeNivel3::StaticClass();
}

AInterfaceEnemigo* UJefe3Factory::CrearEnemigo(UWorld* Mundo, FTransform SpawnTransformacion)
{
    if (!Mundo || !Jefe3) return nullptr;

    FActorSpawnParameters SpawnParametros;
    SpawnParametros.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    return Mundo->SpawnActor<AInterfaceEnemigo>(Jefe3, SpawnTransformacion, SpawnParametros);
}
