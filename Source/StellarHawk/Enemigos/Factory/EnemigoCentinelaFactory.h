// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreadorFactory.h"
#include "EnemigoCentinelaFactory.generated.h"

/**
 * 
 */
UCLASS()
class STELLARHAWK_API UEnemigoCentinelaFactory : public UCreadorFactory
{
	GENERATED_BODY()
	
public:
	UEnemigoCentinelaFactory();

public:
	virtual AInterfaceEnemigo* CrearEnemigo(UWorld* Mundo, FTransform SpawnTransformacion) override;

private:
	UPROPERTY()
	TSubclassOf<AInterfaceEnemigo> EnemigoCentinela;
};
