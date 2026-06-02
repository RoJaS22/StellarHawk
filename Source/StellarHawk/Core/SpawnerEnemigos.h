// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerEnemigos.generated.h"

class UCreadorFactory;
class USceneComponent;

UCLASS()
class STELLARHAWK_API ASpawnerEnemigos : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerEnemigos();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	UCreadorFactory* FabricaEnemigo = nullptr;

	FTimerHandle SpawnTimer;

	UFUNCTION()
	void SpawnEnemigo();

	UPROPERTY()
	USceneComponent* SceneRoot;

public:
	void IniciarSpawner(TSubclassOf<class UCreadorFactory> TipoDeFabrica);

};
