// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveJefeNivel9.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

ANaveJefeNivel9::ANaveJefeNivel9()
{
	PrimaryActorTick.bCanEverTick = true;
	EstadoActual = EEstadoEspectro::VisibleAtacando;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/MallaNave/MallaEnemigos/space-fighter-aircraft-with-animated-wings/source/Wraith.Wraith'"));

    if(MeshAsset.Succeeded())
    {
        MallaEnemigo->SetStaticMesh(MeshAsset.Object);
	}
}

void ANaveJefeNivel9::BeginPlay()
{
    Super::BeginPlay();

    // Encontrar al jugador (asumiendo que es el Player 0)
    JugadorObjetivo = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    // Empezar el ciclo del jefe: Comienza visible y luego se camufla
    GetWorldTimerManager().SetTimer(TemporizadorEstado, this, &ANaveJefeNivel9::IniciarCamuflaje, TiempoVisible, false);
}

void ANaveJefeNivel9::IniciarCamuflaje()
{
    EstadoActual = EEstadoEspectro::InvisibleReposicionando;

    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);

    if (JugadorObjetivo)
    {
        FVector DireccionAleatoria = FMath::VRand();

        FVector NuevaPosicion = JugadorObjetivo->GetActorLocation() + (DireccionAleatoria * DistanciaEmboscada);
		NuevaPosicion.Z = 100.0f; // Mantener la misma altura

        SetActorLocation(NuevaPosicion);

        FRotator NuevaRotacion = (JugadorObjetivo->GetActorLocation() - NuevaPosicion).Rotation();
        SetActorRotation(NuevaRotacion);
    }

    GetWorldTimerManager().SetTimer(TemporizadorEstado, this, &ANaveJefeNivel9::EjecutarAdvertencia, TiempoOculto, false);
}

void ANaveJefeNivel9::EjecutarAdvertencia()
{
    EstadoActual = EEstadoEspectro::PreparandoEmboscada;

    if (SonidoAdvertencia)
    {
        UGameplayStatics::PlaySoundAtLocation(this, SonidoAdvertencia, GetActorLocation());
    }

    GetWorldTimerManager().SetTimer(TemporizadorEstado, this, &ANaveJefeNivel9::RevelarYAtacar, TiempoAdvertencia, false);
}

void ANaveJefeNivel9::RevelarYAtacar()
{
    EstadoActual = EEstadoEspectro::VisibleAtacando;

    // 1. Quitar el camuflaje
    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);

    // 2. ¡Atacar!
    // Aquí puedes llamar a tu función existente de disparo, o la del ataque en abanico que hicimos antes.
    // Ej: DispararRafagaEspecial();

    // 3. Reiniciar el ciclo para que vuelva a camuflarse después de un tiempo
    GetWorldTimerManager().SetTimer(TemporizadorEstado, this, &ANaveJefeNivel9::IniciarCamuflaje, TiempoVisible, false);
}
