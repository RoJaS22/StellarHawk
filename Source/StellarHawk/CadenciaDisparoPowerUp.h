// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpsDecorator.h"
#include "CadenciaDisparoPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class STELLARHAWK_API UCadenciaDisparoPowerUp : public UPowerUpsDecorator
{
	GENERATED_BODY()
	
public:
	virtual float GetCadenciaDisparo() const override;
};
