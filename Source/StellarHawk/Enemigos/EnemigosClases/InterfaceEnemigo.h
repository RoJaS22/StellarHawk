// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InterfaceEnemigo.generated.h"

class UStaticMeshComponent;
class UEnemigoState;

UCLASS(Abstract)
class STELLARHAWK_API AInterfaceEnemigo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInterfaceEnemigo();

	UStaticMeshComponent* MallaEnemigo = nullptr;

	UPROPERTY()
	float RadioDeteccion = 700.0f;
	UPROPERTY()
	float GradosVision = 45.0f;

	UPROPERTY()
	float RangoAtaque = 20.0f;
	UPROPERTY()
	float VelocidadAtaque = 1.0f;

	UPROPERTY()
	float VelocidadMovimiento = 300.0f;
	UPROPERTY()
	float VelocidadRotacion = 5.0f;
	UPROPERTY()
	float Tolerancia = 10.0f;

	UPROPERTY()
	float Vida = 100.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Atacar(float DeltaTime) PURE_VIRTUAL(AInterfaceEnemigo::Atacar, );
	virtual void Patrullar(float DeltaTime) PURE_VIRTUAL(AInterfaceEnemigo::Patrullar, );

	virtual void CambiarState(UEnemigoState* NuevoEstado);
	virtual float TakeDamage(float CantidadDanio, struct FDamageEvent const& EventoDanio, class AController* CausanteEvento, AActor* CausanteDanio) override;
	virtual bool VeAlJugador();
	virtual void MirarHacia(FVector UbicacionObjetivo, float DeltaTime);

protected:
	UPROPERTY()
	UEnemigoState* ActualState = nullptr;

};
