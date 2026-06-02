// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerAsteroides.generated.h"

class AAsteroideFugaz;

UCLASS()
class STELLARHAWK_API ASpawnerAsteroides : public AActor
{
	GENERATED_BODY()

public:
	ASpawnerAsteroides();

protected:
	virtual void BeginPlay() override;

private:

	FTimerHandle TimerSpawn;

	void SpawnearAsteroide();

	UPROPERTY(EditAnywhere, Category = "Spawner")
		float TiempoEntreSpawns;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		float TiempoVidaAsteroide;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		float RangoYMin;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		float RangoYMax;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		float RangoZMin;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		float RangoZMax;
};
