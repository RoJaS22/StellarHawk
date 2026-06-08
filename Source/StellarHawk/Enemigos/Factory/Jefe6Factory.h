// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreadorFactory.h"
#include "Jefe6Factory.generated.h"

/**
 * 
 */
UCLASS()
class STELLARHAWK_API UJefe6Factory : public UCreadorFactory
{
	GENERATED_BODY()

public:
	UJefe6Factory();

public:
	virtual AInterfaceEnemigo* CrearEnemigo(UWorld* Mundo, FTransform SpawnTransformacion) override;

private:
	UPROPERTY()
	TSubclassOf<AInterfaceEnemigo> Jefe6;
	
};
