// Fill out your copyright notice in the Description page of Project Settings.


#include "Jefe6Factory.h"
#include "NaveJefeNivel6.h"
#include "UObject/ConstructorHelpers.h"

UJefe6Factory::UJefe6Factory()
{
	Jefe6 = ANaveJefeNivel6::StaticClass();
}

AInterfaceEnemigo* UJefe6Factory::CrearEnemigo(UWorld* Mundo, FTransform SpawnTransformacion)
{
    if (!Mundo || !Jefe6) return nullptr;

    FActorSpawnParameters SpawnParametros;
    SpawnParametros.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    return Mundo->SpawnActor<AInterfaceEnemigo>(Jefe6, SpawnTransformacion, SpawnParametros);
}
