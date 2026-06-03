// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NivelEventTrigger.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnTriggerActivatedSignature, FName, const TArray<FTransform>&);

class UBoxComponent;

UCLASS()
class STELLARHAWK_API ANivelEventTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANivelEventTrigger();

	FOnTriggerActivatedSignature OnTriggerActivated;

	//El ID que coincidirá exactamente con las claves de tu NivelDataAsset (ej. "Zona_Asteroides")
	UPROPERTY(EditAnywhere, Category = "Configuración")
	FName TriggerID;

protected:
	void BeginPlay() override;

	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componentes")
	UBoxComponent* TriggerBox;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	TArray<FTransform> TransformacionesDeSpawn;

	bool bYaActivado;


};
