// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveDecorator.h"
#include "NaveBaseDecorator.generated.h"

/**
 * 
 */
UCLASS()
class STELLARHAWK_API UNaveBaseDecorator : public UNaveDecorator
{
	GENERATED_BODY()
	
public:
	virtual float GetVelocidadMovimiento() const override {return 600.0f;}
	virtual float GetCadenciaDisparo() const override {return 1.5f;}
	virtual bool TieneEscudo() const override {return false;}
	virtual UNaveDecorator* RemoverStat(UClass* StatARemover) override { return nullptr; }
};
