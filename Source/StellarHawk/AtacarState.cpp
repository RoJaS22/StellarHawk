// Fill out your copyright notice in the Description page of Project Settings.


#include "AtacarState.h"
#include "PerseguirState.h"
#include "PatrullarState.h"
#include "NaveEnemiga.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/Engine.h"

void UAtacarState::EntrarState(ANaveEnemiga* Nave)
{
    // Al entrar al estado de ataque, forzamos que pueda disparar casi de inmediato
    // asignándole un valor alto al temporizador.
    Nave->TiempoDesdeUltimoDisparo= Nave->CadenciaDisparo;

}

void UAtacarState::ActualizarState(ANaveEnemiga* Nave, float DeltaTime)
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
    float DistanciaAlJugador = FVector::Dist(UbicacionActual, UbicacionJugador);

    if (DistanciaAlJugador > (Nave->RangoAtaque * 1.1f))
    {
        Nave->CambiarState(NewObject<UPerseguirState>(Nave));
        return;
    }

    FVector Direccion = (UbicacionJugador - UbicacionActual).GetSafeNormal();
    FRotator RotacionObjetivo = UKismetMathLibrary::MakeRotFromX(Direccion);
    FRotator RotacionSuave = FMath::RInterpTo(Nave->GetActorRotation(), RotacionObjetivo, DeltaTime, Nave->VelocidadRotacion * 2.0f);
    Nave->SetActorRotation(RotacionSuave);

    Nave->Atacar(DeltaTime);
}

void UAtacarState::SalirState(ANaveEnemiga* Nave)
{
}
