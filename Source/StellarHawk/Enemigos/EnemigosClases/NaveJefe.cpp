// Fill out your copyright notice in the Description page of Project Settings.
#include "NaveJefe.h"
#include "EstrategiaRegeneracionJefe.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "StellarHawkProjectile.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"

ANaveJefe::ANaveJefe()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

	if (MallaAsset.Succeeded())
	{
		MallaEnemigo->SetStaticMesh(MallaAsset.Object);
	}

	ClaseProyectil = AStellarHawkProjectile::StaticClass();

	RadioDeteccion = 20000.0f;
	GradosVision = 180.0f;

	RangoAtaque = 10000.0f;
	VelocidadAtaque = 1.0f;

	VelocidadMovimiento = 1000.0f;
	VelocidadRotacion = 15.0f;
	Tolerancia = 10.0f;

	VidaMaxima = 1000.0f;
	Vida = VidaMaxima;
}

void ANaveJefe::BeginPlay()
{
	Super::BeginPlay();

	UEstrategiaRegeneracionJefe* EstrategiaJefe =
		NewObject<UEstrategiaRegeneracionJefe>(this);

	SetEstrategia(EstrategiaJefe);
}

void ANaveJefe::Atacar(float DeltaTime)
{
	TiempoDesdeUltimoDisparo += DeltaTime;

	if (TiempoDesdeUltimoDisparo >= VelocidadAtaque && ClaseProyectil)
	{
		TiempoDesdeUltimoDisparo -= VelocidadAtaque;

		FVector UbicacionSpawn = GetActorLocation() + (GetActorForwardVector() * 5000.0f);
		FRotator RotacionSpawn = GetActorRotation();

		FActorSpawnParameters ParametrosSpawn;
		ParametrosSpawn.Owner = this;
		ParametrosSpawn.Instigator = GetInstigator();

		ParametrosSpawn.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(ClaseProyectil, UbicacionSpawn, RotacionSpawn, ParametrosSpawn);
	}
}

void ANaveJefe::Patrullar(float DeltaTime)
{
	if (PuntosRuta.Num() == 0) return;

	FVector UbicacionActual = GetActorLocation();
	FVector UbicacionObjetivo = PuntosRuta[IndicePuntosRutaActual];

	float DistanciaObjetivo = FVector::Dist(UbicacionActual, UbicacionObjetivo);

	if (DistanciaObjetivo <= Tolerancia)
	{
		IndicePuntosRutaActual = (IndicePuntosRutaActual + 1) % PuntosRuta.Num();
		return;
	}

	FVector Direccion = (UbicacionObjetivo - UbicacionActual).GetSafeNormal();
	FVector NuevaUbicacion = UbicacionActual + (Direccion * VelocidadMovimiento * DeltaTime);

	SetActorLocation(NuevaUbicacion);

	MirarHacia(UbicacionObjetivo, DeltaTime);
}

void ANaveJefe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}