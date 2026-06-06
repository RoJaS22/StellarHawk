// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UMaterialInterface;

UCLASS()
class STELLARHAWK_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();

    void ActivarPortal();

    // El nombre exacto del mapa al que viajaremos (ej. "Map_Nivel_02")
    UPROPERTY(EditAnywhere, Category = "Configuración del Nivel")
    FName NombreSiguienteNivel;

protected:
    // La malla visual del portal (un anillo, un vórtice, etc.)
    UPROPERTY()
    UStaticMeshComponent* PortalMesh;

    // La caja que detectará a la nave
    UPROPERTY()
    UBoxComponent* TriggerBox;

    UPROPERTY()
    UMaterialInterface* NuevoMaterial;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
    bool bEstaActivo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
