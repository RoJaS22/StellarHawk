// Fill out your copyright notice in the Description page of Project Settings.


#include "EstrategiaAtaqueSuicida.h"
#include "InterfaceEnemigo.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

UEstrategiaAtaqueSuicida::UEstrategiaAtaqueSuicida()
{
	bModoSuicida = false;
}

void UEstrategiaAtaqueSuicida::EjecutarEstrategia(AInterfaceEnemigo* Nave, float DeltaTime)
{
	if (!Nave) return;

	float PorcentajeVida =
		Nave->GetVida() / Nave->GetVidaMaxima();

	if (PorcentajeVida <= 0.20f)
	{
		bModoSuicida = true;
	}

	if (!bModoSuicida)
	{
		return;
	}

	APawn* Jugador =
		UGameplayStatics::GetPlayerPawn(
			Nave->GetWorld(),
			0
		);

	if (!Jugador)
	{
		return;
	}

	FVector Direccion =
		(Jugador->GetActorLocation() - Nave->GetActorLocation())
		.GetSafeNormal();

	FVector NuevaPosicion =
		Nave->GetActorLocation()
		+ Direccion * 1200.0f * DeltaTime;

	Nave->SetActorLocation(NuevaPosicion);

	Nave->MirarHacia(
		Jugador->GetActorLocation(),
		DeltaTime
	);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			5,
			0.0f,
			FColor::Red,
			TEXT("MODO SUICIDA")
		);
	}
}