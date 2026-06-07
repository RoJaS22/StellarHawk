// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NaveBaseDecorator.h"
#include "PowerUpsDecorator.h"
#include "Blueprint/UserWidget.h"
#include "StellarHawkPawn.generated.h"

class UNaveBaseDecorator;
class UStaticMeshComponent;
class UUserWidget;

UCLASS(Blueprintable)
class AStellarHawkPawn : public APawn
{
	GENERATED_BODY()

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;

	/** The camera */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:
	AStellarHawkPawn();

	/** Offset from the ships location to spawn projectiles */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite )
	FVector GunOffset;
	
	/* How fast the weapon will fire */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float FireRate;

	/* The speed our ship moves around the level */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	/** Sound to play each time we fire */
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
	class USoundBase* FireSound;

	// Begin Actor Interface
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End Actor Interface

	/* Fire a shot in the specified direction */
	void FireShot(FVector FireDirection);

	/* Handler for the fire timer expiry */
	void ShotTimerExpired();

	// Static names for axis bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName FireForwardBinding;
	static const FName TurnBinding;

private:

	/* Flag to control firing  */
	uint32 bCanFire : 1;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

public:
	/** Returns ShipMeshComponent subobject **/
	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }
	/** Returns CameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetCameraComponent() const { return CameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

public:
	UPROPERTY()
	UNaveDecorator* StatsActuales = nullptr;

	void BeginPlay() override;

	void AplicarPowerUp(TSubclassOf<UPowerUpsDecorator> ClasePowerUp);

public:
	UFUNCTION()
	void RemoverPowerUp(TSubclassOf<UPowerUpsDecorator> PowerUpARemover);

public:
	UPROPERTY()
	UStaticMeshComponent* MallaEscudo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float Vida = 100.0f;

	// Para calcular el porcentaje de la barra del HUD
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float VidaMaxima = 100.0f;

	float ContadorDanioRecibido = 0.0f;

	virtual float TakeDamage(float CantidadDanio, struct FDamageEvent const& EventoDanio, class AController* CausanteEvento, AActor* CausanteDanio) override;

	void ActualizarVisuales();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidget;

	UPROPERTY()
	UUserWidget* ActualHUDWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> ClaseMenuPausa;

	void TogglePause();

public:
	// Aquí asignarás el Blueprint de tu menú de Game Over desde el editor
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> ClaseMenuGameOver;

	// Función que llamarás cuando la salud llegue a 0
	void ManejarMuerte();
};

