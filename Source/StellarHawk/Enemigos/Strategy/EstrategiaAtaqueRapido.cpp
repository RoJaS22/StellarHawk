// Fill out your copyright notice in the Description page of Project Settings.


#include "EstrategiaAtaqueRapido.h"
#include "InterfaceEnemigo.h"
#include "Engine/Engine.h"

UEstrategiaAtaqueRapido::UEstrategiaAtaqueRapido()
{
	TiempoAcumulado = 0.0f;
	DuracionAtaqueRapido = 3.0f;
	TiempoEntreActivaciones = 6.0f;

	bAtaqueRapidoActivo = false;
	VelocidadAtaqueOriginal = 1.0f;
}

void UEstrategiaAtaqueRapido::EjecutarEstrategia(AInterfaceEnemigo* Nave, float DeltaTime)
{
	if (!Nave) return;

	TiempoAcumulado += DeltaTime;

	if (!bAtaqueRapidoActivo && TiempoAcumulado >= TiempoEntreActivaciones)
	{
		bAtaqueRapidoActivo = true;
		TiempoAcumulado = 0.0f;

		VelocidadAtaqueOriginal = Nave->VelocidadAtaque;

		// Mientras más bajo el valor, más rápido dispara.
		Nave->VelocidadAtaque = 0.25f;

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				1.5f,
				FColor::Orange,
				TEXT("ATAQUE RAPIDO ACTIVADO")
			);
		}
	}

	if (bAtaqueRapidoActivo && TiempoAcumulado >= DuracionAtaqueRapido)
	{
		bAtaqueRapidoActivo = false;
		TiempoAcumulado = 0.0f;

		Nave->VelocidadAtaque = VelocidadAtaqueOriginal;

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				1.5f,
				FColor::White,
				TEXT("ATAQUE RAPIDO TERMINADO")
			);
		}
	}
}

