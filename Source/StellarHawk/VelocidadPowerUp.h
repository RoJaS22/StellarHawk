// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpsDecorator.h"
#include "VelocidadPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class STELLARHAWK_API UVelocidadPowerUp : public UPowerUpsDecorator
{
	GENERATED_BODY()

public:
		virtual float GetVelocidadMovimiento() const override;
	
};
