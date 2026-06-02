// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnerAsteroides.h"
#include "AsteroideFugaz.h"
#include "TimerManager.h"

ASpawnerAsteroides::ASpawnerAsteroides()
{
	PrimaryActorTick.bCanEverTick = false;

	TiempoEntreSpawns = 2.0f;
	TiempoVidaAsteroide = 5.0f;

	RangoYMin = -800.0f;
	RangoYMax = 800.0f;

	RangoZMin = 100.0f;
	RangoZMax = 500.0f;
}

void ASpawnerAsteroides::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		TimerSpawn,
		this,
		&ASpawnerAsteroides::SpawnearAsteroide,
		TiempoEntreSpawns,
		true
	);
}

void ASpawnerAsteroides::SpawnearAsteroide()
{
	float YRandom = FMath::RandRange(RangoYMin, RangoYMax);
	float ZRandom = FMath::RandRange(RangoZMin, RangoZMax);

	FVector UbicacionSpawn = GetActorLocation() + FVector(0.0f, YRandom, ZRandom);

	AAsteroideFugaz* Asteroide = GetWorld()->SpawnActor<AAsteroideFugaz>(
		AAsteroideFugaz::StaticClass(),
		UbicacionSpawn,
		FRotator::ZeroRotator
		);

	if (Asteroide)
	{
		Asteroide->SetLifeSpan(TiempoVidaAsteroide);
	}
}

