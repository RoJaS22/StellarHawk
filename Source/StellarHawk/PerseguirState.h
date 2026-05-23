// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemigoState.h"
#include "NaveEnemiga.h"
#include "PerseguirState.generated.h"

UCLASS()
class STELLARHAWK_API UPerseguirState : public UEnemigoState
{
	GENERATED_BODY()

public:
    virtual void EntrarState(ANaveEnemiga* Nave) override;
    virtual void ActualizarState(ANaveEnemiga* Nave, float DeltaTime) override;
    virtual void SalirState(ANaveEnemiga* Nave) override;
};
