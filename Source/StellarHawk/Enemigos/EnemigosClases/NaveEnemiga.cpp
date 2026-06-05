// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveEnemiga.h"
#include "Components/StaticMeshComponent.h"
#include "EstrategiaAtaqueRapido.h"
#include "Engine/World.h"
#include "StellarHawkProjectile.h"



// Sets default values
ANaveEnemiga::ANaveEnemiga()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaAsset(TEXT("StaticMesh'/Game/MallaNave/MallaEnemigos/spaceship_extracted/source/SpaceShip.SpaceShip'"));

	if(MallaAsset.Succeeded())
	{
		MallaEnemigo->SetStaticMesh(MallaAsset.Object);
	}

	// Si no dispara comente esta línea, compile, descomente y vuelva a compilar
	Proyectil = AStellarHawkProjectile::StaticClass();


	RadioDeteccion = 10000.0f;
	GradosVision = 45.0f;

	RangoAtaque = 5000.0f;
	VelocidadAtaque = 1.0f;

	VelocidadMovimiento = 500.0f;
	VelocidadRotacion = 5.0f;
	Tolerancia = 10.0f;

	Vida = 200.0f;
}

// Called when the game starts or when spawned
void ANaveEnemiga::BeginPlay()
{
	Super::BeginPlay();

	UEstrategiaAtaqueRapido* EstrategiaRapida =
		NewObject<UEstrategiaAtaqueRapido>(this);

	SetEstrategia(EstrategiaRapida);

	FVector Punto1 = GetActorLocation() + FVector(0, 0, 0);
	FVector Punto2 = GetActorLocation() + FVector(1000, 0, 0);
	FVector Punto3 = GetActorLocation() + FVector(1000, 1000, 0);
	PuntosRuta.Add(Punto1);
	PuntosRuta.Add(Punto2);
	PuntosRuta.Add(Punto3);
}

void ANaveEnemiga::Atacar(float DeltaTime)
{
	TiempoDesdeUltimoDisparo += DeltaTime;

	if (TiempoDesdeUltimoDisparo >= VelocidadAtaque && Proyectil)
	{
		TiempoDesdeUltimoDisparo -= VelocidadAtaque;

		FVector UbicacionSpawn = GetActorLocation() + (GetActorForwardVector() * 700.0f);
		FRotator RotacionSpawn = GetActorRotation();

		FActorSpawnParameters ParametrosSpawn;
		ParametrosSpawn.Owner = this;
		ParametrosSpawn.Instigator = GetInstigator();

		ParametrosSpawn.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(Proyectil, UbicacionSpawn, RotacionSpawn, ParametrosSpawn);
	}
}

void ANaveEnemiga::Patrullar(float DeltaTime)
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

// Called every frame
void ANaveEnemiga::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

