// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrullarState.h"
#include "InterfaceEnemigo.h"
#include "PerseguirState.h"
#include "Kismet/KismetMathLibrary.h"

void UPatrullarState::EntrarState(AInterfaceEnemigo* Nave)
{
    //Nave->IndicePuntosRutaActual = 0;
}


void UPatrullarState::ActualizarState(AInterfaceEnemigo* Nave, float DeltaTime)
{
    if (!Nave) return;

    if(Nave->VeAlJugador())
    {
        UPerseguirState* PerseguirState = NewObject<UPerseguirState>(Nave);
        Nave->CambiarState(PerseguirState);
        return;
	}

    Nave->Patrullar(DeltaTime);
}

void UPatrullarState::SalirState(AInterfaceEnemigo* Nave)
{
}
