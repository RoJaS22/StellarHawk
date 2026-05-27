// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemigoState.generated.h"

class AInterfaceEnemigo;

UCLASS(Abstract)
class STELLARHAWK_API UEnemigoState : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void EntrarState(AInterfaceEnemigo* Nave) PURE_VIRTUAL(UEnemigoState::EntrarState, );
	virtual void ActualizarState(AInterfaceEnemigo* Nave, float DeltaTime) PURE_VIRTUAL(UEnemigoState::ActualizarState, );
	virtual void SalirState(AInterfaceEnemigo* Nave) PURE_VIRTUAL(UEnemigoState::SalirState, );
};
