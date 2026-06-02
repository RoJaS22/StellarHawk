// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeneradorAsteroidesMapa.generated.h"

class UBoxComponent;
class UHierarchicalInstancedStaticMeshComponent;
class AAsteroide;

UCLASS()
class STELLARHAWK_API AGeneradorAsteroidesMapa : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneradorAsteroidesMapa();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    void GenerarMapa();

    /** Volumen que define los límites en el editor (Eje X y Z primordialmente) */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UBoxComponent* SpawnVolumen;

    /** Componente HISM para renderizar cientos de asteroides en un solo Draw Call */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UHierarchicalInstancedStaticMeshComponent* AsteroideHISM;

    /** Cantidad de asteroides que se generarán en esta zona */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asteroid Setup", meta = (ClampMin = "0"))
    int32 CantidadAsteroides;
    /** Escala mínima para la aleatoriedad */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asteroid Setup")
    float MinEscala;

    /** Escala máxima para la aleatoriedad */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asteroid Setup")
    float MaxEscala;

    UPROPERTY(EditAnywhere, Category = "Asteroid Setup")
    TSubclassOf<AActor> ClaseAsteroide;
    UPROPERTY()
    TArray<AAsteroide*> AsteroidesSpawneados;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
