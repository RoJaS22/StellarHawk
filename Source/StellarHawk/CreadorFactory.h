// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CreadorFactory.generated.h"

class AInterfaceEnemigo;
/**
 * 
 */
UCLASS(Abstract)
class STELLARHAWK_API UCreadorFactory : public UObject
{
	GENERATED_BODY()
	
public:
    UFUNCTION()
    AInterfaceEnemigo* SpawnearEnemigo(UWorld* Mundo, FTransform SpawnTransformacion, int32 NivelEnemigo);

protected:
    virtual AInterfaceEnemigo* CrearEnemigo(UWorld* Mundo, FTransform SpawnTransformacion) PURE_VIRTUAL(UCreadorFactory::CrearEnemigo, return nullptr;);
};
