// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveJefeNivel6.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "EnemigoBaseFactory.h"
#include "UObject/ConstructorHelpers.h"

ANaveJefeNivel6::ANaveJefeNivel6()
{
	VidaMaxima = 1500.0f;

    //Fabrica = NewObject<UCreadorFactory>(this, UEnemigoBaseFactory::StaticClass());
}

void ANaveJefeNivel6::BeginPlay()
{
    Super::BeginPlay();

    // Iniciamos el temporizador para que llame a la función cada un minuto (TiempoEntreInvocaciones)
    // El último parámetro 'true' hace que el temporizador sea un bucle infinito.
    GetWorldTimerManager().SetTimer(
        TemporizadorInvocacion,
        this,
        &ANaveJefeNivel6::SpawnearOleadaAliados,
        TiempoEntreInvocaciones,
        true
    );
}

void ANaveJefeNivel6::SpawnearOleadaAliados()
{
    if (!Fabrica) return;

    UWorld* World = GetWorld();
    if (!World) return;

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();
   
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    FVector UbicacionBase = GetActorLocation();
    FRotator RotacionBase = GetActorRotation();

    for (int32 i = 0; i < CantidadAliadosPorMinuto; i++)
    {
        FTransform TransformacionFinal = FTransform::Identity;

        float DesfaseLateral = (i - (CantidadAliadosPorMinuto - 1) / 2.0f) * DistanciaSeparacionSpawn;

        FVector PosicionSpawn = UbicacionBase + (GetActorRightVector() * DesfaseLateral);

        PosicionSpawn -= (GetActorForwardVector() * 100.0f);
        
        TransformacionFinal = FTransform(RotacionBase, PosicionSpawn);

        AInterfaceEnemigo* NuevoEnemigo = Cast<AInterfaceEnemigo>(Fabrica->SpawnearEnemigo(GetWorld(), TransformacionFinal, 1));

    }
}
