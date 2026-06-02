// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NaveDecorator.generated.h"

/**
 * 
 */
UCLASS()
class STELLARHAWK_API UNaveDecorator : public UObject
{
	GENERATED_BODY()
	
public:
	virtual float GetVelocidadMovimiento() const PURE_VIRTUAL(UNaveDecorator::GetVelocidadMovimiento, return 0.0f;);
	virtual float GetCadenciaDisparo() const PURE_VIRTUAL(UNaveDecorator::GetCadenciaDisparo, return 0.0f;);
	virtual bool TieneEscudo() const PURE_VIRTUAL(UNaveDecorator::TieneEscudo, return false;);
	virtual UNaveDecorator* RemoverStat(UClass* StatARemover) PURE_VIRTUAL(UNaveDecorator::RemoverStat, return nullptr;);
	
};
