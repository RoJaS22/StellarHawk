// Fill out your copyright notice in the Description page of Project Settings.


#include "EstrategiaRegeneracionJefe.h"
#include "InterfaceEnemigo.h"
#include "Engine/Engine.h"

UEstrategiaRegeneracionJefe::UEstrategiaRegeneracionJefe()
{
	bYaSeRegenero = false;
	PorcentajeRegeneracion = 0.25f;
}

void UEstrategiaRegeneracionJefe::EjecutarEstrategia(AInterfaceEnemigo* Nave, float DeltaTime)
{
	if (!Nave) return;

	if (bYaSeRegenero) return;

	float VidaActual = Nave->GetVida();
	float VidaMaxima = Nave->GetVidaMaxima();

	if (VidaActual <= VidaMaxima * 0.5f)
	{
		float CantidadCuracion = VidaMaxima * PorcentajeRegeneracion;

		Nave->Curar(CantidadCuracion);

		bYaSeRegenero = true;

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				2.0f,
				FColor::Green,
				TEXT("JEFE SE REGENERA")
			);
		}
	}
}