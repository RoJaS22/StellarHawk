// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreadorFactory.h"
#include "Jefe9Factory.generated.h"

/**
 * 
 */
UCLASS()
class STELLARHAWK_API UJefe9Factory : public UCreadorFactory
{
	GENERATED_BODY()

public:
	UJefe9Factory();

public:
	virtual AInterfaceEnemigo* CrearEnemigo(UWorld* Mundo, FTransform SpawnTransformacion) override;

private:
	UPROPERTY()
	TSubclassOf<AInterfaceEnemigo> Jefe9;
	
};
