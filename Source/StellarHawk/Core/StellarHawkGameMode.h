// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StellarHawkGameMode.generated.h"

UCLASS(MinimalAPI)
class AStellarHawkGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AStellarHawkGameMode();

protected:
	void BeginPlay() override;	

protected:
	// Función lógica que decide qué Pawn spawnear para el jugador
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

};



