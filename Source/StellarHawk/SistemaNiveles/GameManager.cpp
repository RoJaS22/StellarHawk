// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "Engine/Engine.h"

// Inicialización del Singleton
AGameManager* AGameManager::Instancia = nullptr;

AGameManager::AGameManager()
{
	PrimaryActorTick.bCanEverTick = false;

	Puntos = 0;
	EnemigosDestruidos = 0;
	AsteroidesDestruidos = 0;
	bGameOver = false;
}

void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	if (Instancia == nullptr)
	{
		Instancia = this;

		GEngine->AddOnScreenDebugMessage(
			-1,
			5.0f,
			FColor::Green,
			TEXT("GameManager Singleton creado")
		);
	}
	else
	{
		Destroy();
	}
}

AGameManager* AGameManager::GetInstancia()
{
	return Instancia;
}

void AGameManager::AgregarPuntos(int32 Cantidad)
{
	Puntos += Cantidad;

	GEngine->AddOnScreenDebugMessage(
		-1,
		2.0f,
		FColor::Yellow,
		FString::Printf(TEXT("Puntos: %d"), Puntos)
	);
}

void AGameManager::RegistrarEnemigoDestruido()
{
	EnemigosDestruidos++;

	AgregarPuntos(100);

	GEngine->AddOnScreenDebugMessage(
		-1,
		2.0f,
		FColor::Cyan,
		FString::Printf(
			TEXT("Enemigos destruidos: %d"),
			EnemigosDestruidos
		)
	);
}

void AGameManager::RegistrarAsteroideDestruido()
{
	AsteroidesDestruidos++;

	AgregarPuntos(50);

	GEngine->AddOnScreenDebugMessage(
		-1,
		2.0f,
		FColor::Cyan,
		FString::Printf(
			TEXT("Asteroides destruidos: %d"),
			AsteroidesDestruidos
		)
	);
}

void AGameManager::GameOver()
{
	if (bGameOver)
	{
		return;
	}

	bGameOver = true;

	GEngine->AddOnScreenDebugMessage(
		-1,
		10.0f,
		FColor::Red,
		TEXT("GAME OVER")
	);
}

bool AGameManager::EsGameOver() const
{
	return bGameOver;
}
