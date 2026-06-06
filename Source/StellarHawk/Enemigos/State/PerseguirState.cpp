// Fill out your copyright notice in the Description page of Project Settings.


#include "PerseguirState.h"
#include "PatrullarState.h"
#include "InterfaceEnemigo.h"
#include "AtacarState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"

void UPerseguirState::EntrarState(AInterfaceEnemigo* Nave)
{
	Nave->VelocidadMovimiento *= 1.5f;
    GEngine->AddOnScreenDebugMessage(
        -1,             // Clave (-1 crea un nuevo mensaje en cada llamada)
        5.f,            // Tiempo que durará en pantalla (segundos)
        FColor::Yellow, // Color del texto
        TEXT("Persiguiendo") // El texto a mostrar (usa siempre TEXT())
    );
}

void UPerseguirState::ActualizarState(AInterfaceEnemigo* Nave, float DeltaTime)
{
    if (!Nave) return;

    if (!Nave->VeAlJugador())
    {
        Nave->CambiarState(NewObject<UPatrullarState>(Nave));
        return;
    }
    
    APawn* Jugador = UGameplayStatics::GetPlayerPawn(Nave->GetWorld(), 0);
    if (!Jugador) return;

    FVector UbicacionActual = Nave->GetActorLocation();
    FVector UbicacionJugador = Jugador->GetActorLocation();

    FVector Direccion = (UbicacionJugador - UbicacionActual).GetSafeNormal();
    float DistanciaAlJugador = FVector::Dist(UbicacionActual, UbicacionJugador);

    if (DistanciaAlJugador <= Nave->RangoAtaque)
    {
        Nave->CambiarState(NewObject<UAtacarState>(Nave));
        return;
	}
    else
    {
        FVector NuevaUbicacion = UbicacionActual + (Direccion * Nave->VelocidadMovimiento * DeltaTime);
        Nave->SetActorLocation(NuevaUbicacion);
    }

	Nave->MirarHacia(UbicacionJugador, DeltaTime);
}

void UPerseguirState::SalirState(AInterfaceEnemigo* Nave)
{
    Nave->VelocidadMovimiento /= 1.5f;
}
