// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreadorFactory.h"
#include "EnemigoTanqueFactory.generated.h"

/**
 * 
 */
UCLASS()
class STELLARHAWK_API UEnemigoTanqueFactory : public UCreadorFactory
{
	GENERATED_BODY()
	
public:
	UEnemigoTanqueFactory();

public:
	virtual AInterfaceEnemigo* CrearEnemigo(UWorld* Mundo, FTransform SpawnTransformacion) override;

private:
	UPROPERTY()
	TSubclassOf<AInterfaceEnemigo> EnemigoTanque;
};
