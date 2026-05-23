// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NaveEnemiga.generated.h"

class UStaticMeshComponent;
class UEnemigoState;

UCLASS()
class STELLARHAWK_API ANaveEnemiga : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANaveEnemiga();

	UStaticMeshComponent* MallaNaveEnemiga;

    UPROPERTY()
    TArray<FVector> PuntosRuta;

    UPROPERTY()
    float VelocidadMovimiento = 600.0f;

    UPROPERTY()
    float VelocidadRotacion = 5.0f;

    int32 IndicePuntosRutaActual = 0;
    float Tolerancia = 10.0f;

	UPROPERTY()
	float RadioDeteccion = 700.0f;

	bool VeAlJugador();

	UPROPERTY()
	float GradosVision = 45.0f;

	UPROPERTY()
	float RangoAtaque = 400.0f;

	UPROPERTY()
	TSubclassOf<AActor> Proyectil;

	UPROPERTY()
	float CadenciaDisparo = 0.5f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CambiarState(UEnemigoState* NuevoState);

	virtual void Atacar(float DeltaTime);

	float TiempoDesdeUltimoDisparo = 0.0f;

protected:
	UPROPERTY()
	UEnemigoState* ActualState = nullptr;

public:
	virtual float TakeDamage(float CantidadDanio, struct FDamageEvent const& EventoDanio, class AController* CausanteEvento, AActor* CausanteDanio) override;

	UPROPERTY()
	float Vida = 100.0f;
};
