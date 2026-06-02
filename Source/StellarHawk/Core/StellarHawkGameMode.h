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
};



