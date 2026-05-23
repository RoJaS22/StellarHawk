// Copyright Epic Games, Inc. All Rights Reserved.

#include "StellarHawkPawn.h"
#include "StellarHawkProjectile.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/CollisionProfile.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "EscudoPowerUp.h"

const FName AStellarHawkPawn::MoveForwardBinding("MoveForward");
const FName AStellarHawkPawn::MoveRightBinding("MoveRight");
const FName AStellarHawkPawn::FireForwardBinding("FireForward");
const FName AStellarHawkPawn::FireRightBinding("FireRight");

AStellarHawkPawn::AStellarHawkPawn()
{	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

	// Movement
	MoveSpeed = 1000.0f;
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;

	//Malla del escudo
	MallaEscudo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldVisualComp"));
	MallaEscudo->SetupAttachment(RootComponent);
	MallaEscudo->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MallaEscudo->SetVisibility(false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (SphereMesh.Succeeded())
	{
		MallaEscudo->SetStaticMesh(SphereMesh.Object);
		MallaEscudo->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));
	}

}

void AStellarHawkPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis(FireForwardBinding);
	PlayerInputComponent->BindAxis(FireRightBinding);
}

void AStellarHawkPawn::Tick(float DeltaSeconds)
{
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * StatsActuales->GetVelocidadMovimiento() * DeltaSeconds;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}
	
	// Create fire direction vector
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);

	// Try and fire a shot
	FireShot(FireDirection);
}

void AStellarHawkPawn::FireShot(FVector FireDirection)
{
	// If it's ok to fire again
	if (bCanFire == true)
	{
		// If we are pressing fire stick in a direction
		if (FireDirection.SizeSquared() > 0.0f)
		{
			const FRotator FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				// spawn the projectile
				World->SpawnActor<AStellarHawkProjectile>(SpawnLocation, FireRotation);
			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AStellarHawkPawn::ShotTimerExpired, FireRate);

			// try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bCanFire = false;
		}
	}
}

void AStellarHawkPawn::ShotTimerExpired()
{
	bCanFire = true;
}

void AStellarHawkPawn::BeginPlay()
{
	Super::BeginPlay();

	
	StatsActuales = NewObject<UNaveBaseDecorator>(this);
}

void AStellarHawkPawn::AplicarPowerUp(TSubclassOf<UPowerUpsDecorator> ClasePowerUp)
{
	if (ClasePowerUp && StatsActuales)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,             // Clave (-1 crea un nuevo mensaje en cada llamada)
			5.f,            // Tiempo que durará en pantalla (segundos)
			FColor::Yellow, // Color del texto
			TEXT("PowerUp aplicado") // El texto a mostrar (usa siempre TEXT())
		);

		// 2. Creamos la nueva mejora (ej: Escudo)
		UPowerUpsDecorator* NuevoPowerUp = NewObject<UPowerUpsDecorator>(this, ClasePowerUp);

		// 3. El escudo envuelve a las estadísticas anteriores
		NuevoPowerUp->InicializarDecorator(StatsActuales);

		// 4. El escudo se convierte en la nueva "capa exterior"
		StatsActuales = NuevoPowerUp;

		FTimerHandle PowerUpTimer;
		FTimerDelegate TimerDel;

		// Vinculamos la función de limpieza pasándole la clase como parámetro
		TimerDel.BindUFunction(this, FName("RemoverPowerUp"), ClasePowerUp);

		// Activamos el temporizador para dentro de 10.0 segundos (false = no se repite)
		GetWorld()->GetTimerManager().SetTimer(PowerUpTimer, TimerDel, 10.0f, false);
	}
	ActualizarVisuales();
}

void AStellarHawkPawn::RemoverPowerUp(TSubclassOf<UPowerUpsDecorator> PowerUpARemover)
{
	if (StatsActuales && PowerUpARemover)
	{
		// Llamamos a nuestra función recursiva. 
		// Actualiza el puntero de CurrentStats en caso de que se haya eliminado la capa más externa.
		StatsActuales = StatsActuales->RemoverStat(PowerUpARemover);
	}
	ActualizarVisuales();
}

float AStellarHawkPawn::TakeDamage(float CantidadDanio, FDamageEvent const& EventoDanio, AController* CausanteEvento, AActor* CausanteDanio)
{
	if (!StatsActuales) return 0.0f;

	// 1. EL DECORADOR ACTÚA DE GUARDIÁN
	if (StatsActuales->TieneEscudo())
	{
		// ¡El escudo absorbe todo el daño!
		// Opcional: Aquí podrías reproducir un sonido de "Rebote láser"

		// MECÁNICA CLÁSICA: El escudo se destruye al recibir 1 disparo
		// Llamamos a nuestra función de limpieza para que busque el escudo en la cadena y lo quite
		RemoverPowerUp(UEscudoPowerUp::StaticClass());

		// Devolvemos 0 porque la salud real no sufrió daño
		return 0.0f;
	}

	// 2. RECIBIMOS EL DAÑO NORMAL
	Vida -= CantidadDanio;

	// 3. COMPROBAR MUERTE
	if (Vida <= 0.0f)
	{
		// Aquí iría tu lógica de muerte (Explosión, Game Over, etc.)
		Destroy();
	}

	return CantidadDanio;
}

void AStellarHawkPawn::ActualizarVisuales()
{
	if (StatsActuales)
	{
		// El decorador devolverá true si hay un escudo en la cadena, o false si no lo hay.
		// SetVisibility acepta directamente ese booleano. ¡Súper limpio!
		MallaEscudo->SetVisibility(StatsActuales->TieneEscudo());
	}
}

