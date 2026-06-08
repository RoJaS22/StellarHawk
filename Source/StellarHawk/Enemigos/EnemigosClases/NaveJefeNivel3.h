// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveJefe.h"
#include "NaveJefeNivel3.generated.h"

/**
 * 
 */
UCLASS()
class STELLARHAWK_API ANaveJefeNivel3 : public ANaveJefe
{
	GENERATED_BODY()

public:
	ANaveJefeNivel3();

protected:
	virtual void BeginPlay() override;
	
protected:
    // Temporizadores
    FTimerHandle TemporizadorAtaqueEspecial;
    FTimerHandle TemporizadorRafaga;

    // Configuración del ataque
    UPROPERTY(EditAnywhere, Category = "Ataque Especial")
    float TiempoCooldownEspecial = 10.0f;

    UPROPERTY(EditAnywhere, Category = "Ataque Especial")
    int32 CantidadProyectilesRafaga = 30;

    UPROPERTY(EditAnywhere, Category = "Ataque Especial")
    float TiempoEntreProyectiles = 0.1f;

    UPROPERTY(EditAnywhere, Category = "Ataque Especial")
    float AnguloTotalApertura = 90.0f;

    // Variables de control de estado
    int32 ProyectilesDisparadosActuales;
    bool bEstaHaciendoAtaqueEspecial;

    // Funciones
    void IniciarAtaqueEspecial();
    void DispararProyectilEspecial();
    void FinalizarAtaqueEspecial();
	
};
