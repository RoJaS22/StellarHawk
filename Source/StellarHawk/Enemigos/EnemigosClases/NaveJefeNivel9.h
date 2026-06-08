// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveJefe.h"
#include "NaveJefeNivel9.generated.h"

/**
 * 
 */

UENUM()
enum class EEstadoEspectro : uint8
{
    VisibleAtacando,
    InvisibleReposicionando,
    PreparandoEmboscada
};

UCLASS()
class STELLARHAWK_API ANaveJefeNivel9 : public ANaveJefe
{
	GENERATED_BODY()
	
public:
    ANaveJefeNivel9();

protected:
    virtual void BeginPlay() override;

    EEstadoEspectro EstadoActual;

    FTimerHandle TemporizadorEstado;

    // Tiempos para cada fase
    UPROPERTY(EditAnywhere, Category = "Espectro | Tiempos")
    float TiempoVisible = 4.0f; 

    UPROPERTY(EditAnywhere, Category = "Espectro | Tiempos")
    float TiempoOculto = 3.0f; 

    UPROPERTY(EditAnywhere, Category = "Espectro | Tiempos")
    float TiempoAdvertencia = 0.8f; 

    UPROPERTY(EditAnywhere, Category = "Espectro | Movimiento")
    float DistanciaEmboscada = 1500.0f; // A qué distancia del jugador reaparece

    UPROPERTY(EditAnywhere, Category = "Espectro | Efectos")
    class USoundBase* SonidoAdvertencia;

    AActor* JugadorObjetivo;

    // --- Funciones de Estado ---
    void IniciarCamuflaje();
    void EjecutarAdvertencia();
    void RevelarYAtacar();
};
