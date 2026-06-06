// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoTanqueFactory.h"
#include "NaveTanque.h"
#include "UObject/ConstructorHelpers.h"

UEnemigoTanqueFactory::UEnemigoTanqueFactory()
{
	EnemigoTanque = ANaveTanque::StaticClass();
}

AInterfaceEnemigo* UEnemigoTanqueFactory::CrearEnemigo(UWorld* Mundo, FTransform SpawnTransformacion)
{
    if (!Mundo || !EnemigoTanque) return nullptr;

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

    return Mundo->SpawnActor<AInterfaceEnemigo>(EnemigoTanque, SpawnTransformacion, SpawnParametros);
}
