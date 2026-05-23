// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemigoState.generated.h"

class ANaveEnemiga;

UCLASS()
class STELLARHAWK_API UEnemigoState : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void EntrarState(ANaveEnemiga* Nave) PURE_VIRTUAL(UEnemigoState::EntrarState, );
	virtual void ActualizarState(ANaveEnemiga* Nave, float DeltaTime) PURE_VIRTUAL(UEnemigoState::ActualizarState, );
	virtual void SalirState(ANaveEnemiga* Nave) PURE_VIRTUAL(UEnemigoState::SalirState, );
};
