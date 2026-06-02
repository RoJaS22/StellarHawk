// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpsDecorator.h"
#include "EscudoPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class STELLARHAWK_API UEscudoPowerUp : public UPowerUpsDecorator
{
	GENERATED_BODY()
	
public:
	virtual bool TieneEscudo() const override;
};
