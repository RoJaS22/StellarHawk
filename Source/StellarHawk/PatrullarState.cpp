// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrullarState.h"
#include "NaveEnemiga.h"
#include "PerseguirState.h"
#include "Kismet/KismetMathLibrary.h"

void UPatrullarState::EntrarState(ANaveEnemiga* Nave)
{
    Nave->IndicePuntosRutaActual = 0;
}


void UPatrullarState::ActualizarState(ANaveEnemiga* Nave, float DeltaTime)
{
    if (!Nave) return;

    if(Nave->VeAlJugador())
    {
        UPerseguirState* PerseguirState = NewObject<UPerseguirState>(Nave);
        Nave->CambiarState(PerseguirState);
        return;
	}

    if (Nave->PuntosRuta.Num() == 0) return;

    FVector UbicacionActual = Nave->GetActorLocation();
    FVector UbicacionObjetivo = Nave->PuntosRuta[Nave->IndicePuntosRutaActual];

    float DistanciaObjetivo = FVector::Dist(UbicacionActual, UbicacionObjetivo);
    if (DistanciaObjetivo <= Nave->Tolerancia)
    {
        Nave->IndicePuntosRutaActual = (Nave->IndicePuntosRutaActual + 1) % Nave->PuntosRuta.Num();
        return; 
    }

    FVector Direccion = (UbicacionObjetivo - UbicacionActual).GetSafeNormal();
    FVector NuevaUbicacion = UbicacionActual + (Direccion * Nave->VelocidadMovimiento * DeltaTime);
    Nave->SetActorLocation(NuevaUbicacion);

    FRotator RotacionObjetivo = UKismetMathLibrary::MakeRotFromX(Direccion);
    FRotator RotacionSuave = FMath::RInterpTo(Nave->GetActorRotation(), RotacionObjetivo, DeltaTime, Nave->VelocidadRotacion);
    Nave->SetActorRotation(RotacionSuave);
}

void UPatrullarState::SalirState(ANaveEnemiga* Nave)
{
}
