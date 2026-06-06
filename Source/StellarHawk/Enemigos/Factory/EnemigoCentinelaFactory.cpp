// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoCentinelaFactory.h"
#include "NaveCentinela.h"
#include "UObject/ConstructorHelpers.h"

UEnemigoCentinelaFactory::UEnemigoCentinelaFactory()
{
	EnemigoCentinela = ANaveCentinela::StaticClass();
}

AInterfaceEnemigo* UEnemigoCentinelaFactory::CrearEnemigo(UWorld* Mundo, FTransform SpawnTransformacion)
{
    if (!Mundo || !EnemigoCentinela) return nullptr;

    /*
    GEngine->AddOnScreenDebugMessage(
        -1,             // Clave (-1 crea un nuevo mensaje en cada llamada)
        5.f,            // Tiempo que durará en pantalla (segundos)
        FColor::Yellow, // Color del texto
        TEXT("EnemigoBaseFactory Sirve") // El texto a mostrar (usa siempre TEXT())
    );
    */

    FActorSpawnParameters SpawnParametros;
    SpawnParametros.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    return Mundo->SpawnActor<AInterfaceEnemigo>(EnemigoCentinela, SpawnTransformacion, SpawnParametros);
}
