// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Asteroide.generated.h"

UCLASS()
class STELLARHAWK_API AAsteroide : public AActor
{
	GENERATED_BODY()

public:
	AAsteroide();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Malla;

	UPROPERTY(EditAnywhere, Category = "Asteroide")
		float Velocidad;

	UPROPERTY(EditAnywhere, Category = "Asteroide")
		float Vida;

	UPROPERTY(EditAnywhere, Category = "Asteroide")
		FVector DireccionMovimiento;

public:

	virtual void Mover(float DeltaTime);

	virtual void RecibirDanio(float Danio);

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

};
