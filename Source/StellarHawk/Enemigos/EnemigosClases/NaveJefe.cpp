// Fill out your copyright notice in the Description page of Project Settings.
#include "NaveJefe.h"
#include "EstrategiaRegeneracionJefe.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "StellarHawkProjectile.h"
#include "UObject/ConstructorHelpers.h"

ANaveJefe::ANaveJefe()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

	if (MallaAsset.Succeeded())
	{
		MallaEnemigo->SetStaticMesh(MallaAsset.Object);
	}

	Proyectil = AStellarHawkProjectile::StaticClass();

	RadioDeteccion = 700.0f;
	GradosVision = 45.0f;

	RangoAtaque = 500.0f;
	VelocidadAtaque = 1.0f;

	VelocidadMovimiento = 500.0f;
	VelocidadRotacion = 5.0f;
	Tolerancia = 10.0f;

	VidaMaxima = 500.0f;
	Vida = VidaMaxima;
}

void ANaveJefe::BeginPlay()
{
	Super::BeginPlay();

	UEstrategiaRegeneracionJefe* EstrategiaJefe =
		NewObject<UEstrategiaRegeneracionJefe>(this);

	SetEstrategia(EstrategiaJefe);

	FVector Punto1 = GetActorLocation() + FVector(0, 0, 0);
	FVector Punto2 = GetActorLocation() + FVector(1000, 0, 0);
	FVector Punto3 = GetActorLocation() + FVector(1000, 1000, 0);

	PuntosRuta.Add(Punto1);
	PuntosRuta.Add(Punto2);
	PuntosRuta.Add(Punto3);
}

void ANaveJefe::Atacar(float DeltaTime)
{
	TiempoDesdeUltimoDisparo += DeltaTime;

	if (TiempoDesdeUltimoDisparo >= VelocidadAtaque && Proyectil)
	{
		TiempoDesdeUltimoDisparo -= VelocidadAtaque;

		FVector UbicacionSpawn = GetActorLocation() + (GetActorForwardVector() * 30.0f);
		FRotator RotacionSpawn = GetActorRotation();

		FActorSpawnParameters ParametrosSpawn;
		ParametrosSpawn.Owner = this;
		ParametrosSpawn.Instigator = GetInstigator();

		ParametrosSpawn.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(Proyectil, UbicacionSpawn, RotacionSpawn, ParametrosSpawn);
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