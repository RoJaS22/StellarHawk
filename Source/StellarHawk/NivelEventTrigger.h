// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NivelEventTrigger.generated.h"

class UBoxComponent;

USTRUCT()
struct FEnemigoSpawnRequest
{
	GENERATED_BODY()

	FName IDTipoEnemigo;

	UPROPERTY()
	FVector SpawnOffset;

};

UCLASS()
class STELLARHAWK_API ANivelEventTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANivelEventTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	UBoxComponent* TriggerVolumen;

	UPROPERTY()
	TArray<FEnemigoSpawnRequest> EnemigosSpawnear;

	/** Función que se ejecutará cuando algo entre al Trigger */
	UFUNCTION()
	void OnVolumeOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

private:
	bool bHaSidoActivado;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
