// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUpItem.h"
#include "GeneradorPowerUps.generated.h"

UCLASS()
class STELLARHAWK_API AGeneradorPowerUps : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneradorPowerUps();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
    // Lista de las diferentes clases de Power-Ups que puede crear (Cura, Arma, etc.)
    UPROPERTY(EditAnywhere, Category = "Configuración del Generador")
    TArray<TSubclassOf<APowerUpItem>> ClasesDePowerUps;

    // Cuántos objetos quieres que haya flotando en total en el mapa
    UPROPERTY(EditAnywhere, Category = "Configuración del Generador")
    int32 CantidadAGenerar;

    // Los límites físicos de tu nivel donde es seguro que aparezcan
    UPROPERTY(EditAnywhere, Category = "Configuración del Generador")
    FVector2D LimitesEjeX;

    UPROPERTY(EditAnywhere, Category = "Configuración del Generador")
    FVector2D LimitesEjeY;

};
