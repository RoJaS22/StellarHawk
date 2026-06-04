// Fill out your copyright notice in the Description page of Project Settings.


#include "EstrategiaExplosionTanque.h"
#include "InterfaceEnemigo.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

UEstrategiaExplosionTanque::UEstrategiaExplosionTanque()
{
	bExplosionActivada = false;
	TiempoExplosion = 0.0f;
	TiempoEntreExplosiones = 2.0f;
}

void UEstrategiaExplosionTanque::EjecutarEstrategia(AInterfaceEnemigo* Nave, float DeltaTime)
{
	if (!Nave) return;

	float VidaActual = Nave->GetVida();
	float VidaMaxima = Nave->GetVidaMaxima();

	if (VidaActual <= VidaMaxima * 0.5f)
	{
		bExplosionActivada = true;
	}

	if (bExplosionActivada)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			0.0f,
			FColor::Red,
			TEXT("MODO EXPLOSION ACTIVADO")
		);
	}

	if (!bExplosionActivada) return;

	TiempoExplosion += DeltaTime;

	if (TiempoExplosion >= TiempoEntreExplosiones)
	{
		TiempoExplosion = 0.0f;

		FVector Ubicacion = Nave->GetActorLocation();

		DrawDebugSphere(
			Nave->GetWorld(),
			Ubicacion,
			250.0f,
			24,
			FColor::Red,
			false,
			0.5f
		);

		UGameplayStatics::ApplyRadialDamage(
			Nave->GetWorld(),
			40.0f,
			Ubicacion,
			250.0f,
			nullptr,
			TArray<AActor*>(),
			Nave,
			nullptr,
			true
		);
	}
}

