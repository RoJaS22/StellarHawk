// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroideDestructible.h"
#include "GameManager.h"

AAsteroideDestructible::AAsteroideDestructible()
{
	Velocidad = 0.0f;
	Vida = 100.0f;
	DireccionMovimiento = FVector(0.0f, 0.0f, 0.0f);
}

void AAsteroideDestructible::AlDestruirse()
{
	if (AGameManager::GetInstancia())
	{
		AGameManager::GetInstancia()->RegistrarAsteroideDestruido();
	}
}