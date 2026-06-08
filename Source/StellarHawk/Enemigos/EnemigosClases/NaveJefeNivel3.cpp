// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveJefeNivel3.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

ANaveJefeNivel3::ANaveJefeNivel3()
{
	VidaMaxima = 1000.0f;

    bEstaHaciendoAtaqueEspecial = false;
    ProyectilesDisparadosActuales = 0; 

	DistanciaDisparar = 5000.0f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaAsset(TEXT("StaticMesh'/Game/MallaNave/MallaEnemigos/luminaris-starship/source/9d06199c2def4d1b95bc7e37e8f30cf1_fbx.9d06199c2def4d1b95bc7e37e8f30cf1_fbx'"));
    
    if(MallaAsset.Succeeded())
    {
        MallaEnemigo->SetStaticMesh(MallaAsset.Object);
	}

}

void ANaveJefeNivel3::BeginPlay()
{
	Super::BeginPlay();

    GetWorldTimerManager().SetTimer(
        TemporizadorAtaqueEspecial,
        this,
        &ANaveJefeNivel3::IniciarAtaqueEspecial,
        TiempoCooldownEspecial,
        true
    );
}

void ANaveJefeNivel3::IniciarAtaqueEspecial()
{
    // Prevenir que se active si ya está atacando
    if (bEstaHaciendoAtaqueEspecial) return;

    bEstaHaciendoAtaqueEspecial = true;
    ProyectilesDisparadosActuales = 0;

    GetWorldTimerManager().SetTimer(
        TemporizadorRafaga,
        this,
        &ANaveJefeNivel3::DispararProyectilEspecial,
        TiempoEntreProyectiles,
        true,
        0.0f
    );
}

void ANaveJefeNivel3::DispararProyectilEspecial()
{
    if (!ClaseProyectil) return; 

    float Fraccion = (CantidadProyectilesRafaga > 1) ?
        (float)ProyectilesDisparadosActuales / (float)(CantidadProyectilesRafaga - 1) : 0.0f;

    float AnguloActual = FMath::Lerp(-AnguloTotalApertura / 2.0f, AnguloTotalApertura / 2.0f, Fraccion);

    FRotator RotacionDisparo = GetActorRotation();
    RotacionDisparo.Yaw += AnguloActual; // Modificamos el eje Z (Yaw) para disparos horizontales

    FVector UbicacionDisparo = GetActorLocation() + (GetActorForwardVector() * 5000.0f);

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    GetWorld()->SpawnActor<AActor>(ClaseProyectil, UbicacionDisparo, RotacionDisparo, SpawnParams);

    ProyectilesDisparadosActuales++;

    if (ProyectilesDisparadosActuales >= CantidadProyectilesRafaga)
    {
        FinalizarAtaqueEspecial();
    }
}

void ANaveJefeNivel3::FinalizarAtaqueEspecial()
{
    // Detener la ráfaga
    GetWorldTimerManager().ClearTimer(TemporizadorRafaga);

    bEstaHaciendoAtaqueEspecial = false;

}