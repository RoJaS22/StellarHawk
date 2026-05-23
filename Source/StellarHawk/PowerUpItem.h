// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUpItem.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UPowerUpsDecorator;

UCLASS()
class STELLARHAWK_API APowerUpItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUpItem();

protected:
    UPROPERTY()
    USphereComponent* Colision;

    // Componente visual (La cajita 3D)
    UPROPERTY()
    UStaticMeshComponent* Malla;

    // ¿Qué mejora otorgará esta caja? (Lo configuramos en el Editor)
    UPROPERTY()
    TSubclassOf<UPowerUpsDecorator> PowerUpAplicar;

    // Función que se dispara cuando algo entra en la esfera
    UFUNCTION()
    void AlSolaparse(UPrimitiveComponent* SolapadoComp, AActor* OtroActor, UPrimitiveComponent* OtroComp, int32 IndiceOtroCuerpo, bool bBarrido, const FHitResult& BarridoResultado);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
