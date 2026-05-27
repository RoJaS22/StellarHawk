// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreadorFactory.h"
#include "EnemigoBaseFactory.generated.h"

/**
 * 
 */
UCLASS()
class STELLARHAWK_API UEnemigoBaseFactory : public UCreadorFactory
{
	GENERATED_BODY()

public:
	UEnemigoBaseFactory();

protected:
	virtual AInterfaceEnemigo* CrearEnemigo(UWorld* Mundo, FTransform SpawnTransformacion) override;

private:
	UPROPERTY()
	TSubclassOf<AInterfaceEnemigo> EnemigoBasico;
	
};
