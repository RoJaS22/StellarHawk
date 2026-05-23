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

	// Tiempo en segundos entre cada disparo
	UPROPERTY()
	float CadenciaDisparo = 1.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//void Disparar(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CambiarState(UEnemigoState* NuevoState);

	
	float TiempoDesdeUltimoDisparo;

private:
	UPROPERTY()
	UEnemigoState* ActualState = nullptr;

};
