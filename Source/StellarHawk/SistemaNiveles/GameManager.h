// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameManager.generated.h"

UCLASS()
class STELLARHAWK_API AGameManager : public AActor
{
	GENERATED_BODY()

public:
	AGameManager();

protected:
	virtual void BeginPlay() override;

private:

	// Instancia única del Singleton
	static AGameManager* Instancia;

public:

	// Acceso global
	static AGameManager* GetInstancia();

	// Funciones
	void AgregarPuntos(int32 Cantidad);
	void RegistrarEnemigoDestruido();
	void RegistrarAsteroideDestruido();

	void GameOver();

	bool EsGameOver() const;

private:

	int32 Puntos;

	int32 EnemigosDestruidos;

	int32 AsteroidesDestruidos;

	bool bGameOver;
};