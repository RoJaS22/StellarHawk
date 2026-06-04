// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EstrategiaEnemigo.generated.h"

class AInterfaceEnemigo;

UCLASS()
class STELLARHAWK_API UEstrategiaEnemigo : public UObject
{
	GENERATED_BODY()

public:

	virtual void EjecutarEstrategia(AInterfaceEnemigo* Nave, float DeltaTime);
};
