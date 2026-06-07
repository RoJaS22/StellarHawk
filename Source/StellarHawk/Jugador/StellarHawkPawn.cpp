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
#include "GameManager.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"


const FName AStellarHawkPawn::MoveForwardBinding("MoveForward");
const FName AStellarHawkPawn::MoveRightBinding("MoveRight");
const FName AStellarHawkPawn::FireForwardBinding("FireForward");
const FName AStellarHawkPawn::TurnBinding("Turn");

AStellarHawkPawn::AStellarHawkPawn()
{	
	/*
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("StaticMesh'/Game/MallaNave/gemitest2_Cube.gemitest2_Cube'"));
	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMeshComponent;
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	*/

	UBoxComponent* CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetBoxExtent(FVector(10.0f, 10.0f, 10.0f)); // Ajusta el tamaño según tu nave
	CollisionBox->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	RootComponent = CollisionBox;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMeshAsset(TEXT("StaticMesh'/Game/MallaNave/MallaJugador/gemitest2_Cube.gemitest2_Cube'"));

	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMeshComponent->SetStaticMesh(ShipMeshAsset.Object);
	ShipMeshComponent->SetupAttachment(RootComponent);
	ShipMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = false;
	//CameraBoom->SetUsingAbsoluteRotation(false); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 2500.f;
	CameraBoom->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	CameraBoom->SetRelativeLocation(FVector(-500.f, 0.f, 500.f));
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

	// Cargar HUD
	// y añadir "_C" al final para buscar la clase generada.
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDWidgetObj(TEXT("WidgetBlueprint'/Game/HUD.HUD_C'"));

	if (HUDWidgetObj.Succeeded())
	{
		HUDWidget = HUDWidgetObj.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> MenuPausa(TEXT("WidgetBlueprint'/Game/WBP_PauseMenu.WBP_PauseMenu_C'"));

	if (MenuPausa.Succeeded())
	{
		ClaseMenuPausa = MenuPausa.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> MenuPerder(TEXT("WidgetBlueprint'/Game/WBP_GameOver.WBP_GameOver_C'"));

	if (MenuPerder.Succeeded())
	{
		ClaseMenuGameOver = MenuPerder.Class;
	}
}

void AStellarHawkPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis(FireForwardBinding);
	PlayerInputComponent->BindAxis(TurnBinding);

	FInputActionBinding& PauseBinding = PlayerInputComponent->BindAction("PausarJuego", IE_Pressed, this, &AStellarHawkPawn::TogglePause);
	PauseBinding.bExecuteWhenPaused = true;
}

void AStellarHawkPawn::Tick(float DeltaSeconds)
{
	const float MouseX = GetInputAxisValue(TEXT("Turn"));

	if (MouseX != 0.0f) AddControllerYawInput(MouseX);

	FRotator RotationControlador = FRotator::ZeroRotator;
	if (GetController() != nullptr)
	{
		RotationControlador = GetController()->GetControlRotation();
	}

	FRotator NuevaRotacionPersonaje = FRotator(0.f, RotationControlador.Yaw, 0.f);

	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	const FVector InputLocal = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	const FVector MoveDirection = NuevaRotacionPersonaje.RotateVector(InputLocal);

	const FVector Movement = MoveDirection * StatsActuales->GetVelocidadMovimiento() * DeltaSeconds;

	
	if (Movement.SizeSquared() > 0.0f || GetActorRotation() != NuevaRotacionPersonaje)
	{
		const FRotator RotacionActual = GetActorRotation();
		const FRotator RotacionSuave = FMath::RInterpTo(RotacionActual, NuevaRotacionPersonaje, DeltaSeconds, 15.0f);

		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, RotacionSuave, true, &Hit);

		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, RotacionSuave, true);
		}
	}

	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);

	if(FireForwardValue != 0.0f)
	{
		const FVector FireDirection = GetActorForwardVector();
		FireShot(FireDirection);
	}
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
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AStellarHawkPawn::ShotTimerExpired, StatsActuales->GetCadenciaDisparo());

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

	// HUD
	if (HUDWidget)
	{
		ActualHUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);

		if (ActualHUDWidget)
		{
			ActualHUDWidget->AddToViewport();
		}
	}
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

		UPowerUpsDecorator* NuevoPowerUp = NewObject<UPowerUpsDecorator>(this, ClasePowerUp);
		
		// Inicializamos el decorador pasándole la capa actual de estadísticas para que pueda envolverla
		NuevoPowerUp->InicializarDecorator(StatsActuales);
		StatsActuales = NuevoPowerUp;

		// Temporizador para remover PowerUps
		FTimerHandle PowerUpTimer;
		FTimerDelegate TimerDel;

		TimerDel.BindUFunction(this, FName("RemoverPowerUp"), ClasePowerUp);

		GetWorld()->GetTimerManager().SetTimer(PowerUpTimer, TimerDel, 10.0f, false);
	}
	ActualizarVisuales();
}

void AStellarHawkPawn::RemoverPowerUp(TSubclassOf<UPowerUpsDecorator> PowerUpARemover)
{
	if (StatsActuales && PowerUpARemover)
	{
		StatsActuales = StatsActuales->RemoverStat(PowerUpARemover);
	}
	ActualizarVisuales();
}

float AStellarHawkPawn::TakeDamage(float CantidadDanio, FDamageEvent const& EventoDanio, AController* CausanteEvento, AActor* CausanteDanio)
{
	if (!StatsActuales) return 0.0f;

	if (StatsActuales->TieneEscudo())
	{
		ContadorDanioRecibido += CantidadDanio;
		// ¡El escudo absorbe todo el daño!
		// Opcional: Aquí podrías reproducir un sonido de "Rebote láser"
		if (ContadorDanioRecibido >= 60.0f) {
			RemoverPowerUp(UEscudoPowerUp::StaticClass());
		}

		return 0.0f;
	}

	Vida -= CantidadDanio;

	if (Vida <= 0.0f)
	{
		Vida = 0.0f;

		/*
		if (AGameManager::GetInstancia())
		{
			AGameManager::GetInstancia()->GameOver();
		}
		*/

		ManejarMuerte();
		//Destroy();
	}

	return CantidadDanio;
}

void AStellarHawkPawn::ActualizarVisuales()
{
	if (StatsActuales)
	{
		MallaEscudo->SetVisibility(StatsActuales->TieneEscudo());
	}
}

void AStellarHawkPawn::TogglePause()
{
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);

		APlayerController* PC = Cast<APlayerController>(GetController());
		if (PC)
		{
			PC->bShowMouseCursor = false;

			FInputModeGameOnly InputModeData;
			InputModeData.SetConsumeCaptureMouseDown(false);
			PC->SetInputMode(InputModeData);

			if (FSlateApplication::IsInitialized())
			{
				FSlateApplication::Get().SetAllUserFocusToGameViewport();
			}
			if (GEngine && GEngine->GameViewport)
			{
				GEngine->GameViewport->SetMouseLockMode(EMouseLockMode::LockAlways);
				GEngine->GameViewport->SetMouseCaptureMode(EMouseCaptureMode::CapturePermanently_IncludingInitialMouseDown);
			}
		}

		// NOTA: Tendrías que buscar el Widget del menú y llamar a RemoveFromParent() 
		// para destruirlo, o dejar que la responsabilidad de reanudar sea SOLO del botón "Continuar".
		return;
	}

	if (ClaseMenuPausa)
	{
		UUserWidget* MenuPausa = CreateWidget<UUserWidget>(GetWorld(), ClaseMenuPausa);
		if (MenuPausa)
		{
			MenuPausa->AddToViewport();
			UGameplayStatics::SetGamePaused(GetWorld(), true);

			APlayerController* PC = Cast<APlayerController>(GetController());
			if (PC)
			{
				PC->bShowMouseCursor = true;
				PC->SetInputMode(FInputModeUIOnly());
			}
		}
	}
}

void AStellarHawkPawn::ManejarMuerte()
{
	SetActorHiddenInGame(true); // La hacemos invisible
	SetActorEnableCollision(false); // Evitamos que los enemigos choquen con el fantasma
	SetActorTickEnabled(false); // Apagamos su lógica interna


	if (ClaseMenuGameOver)
	{
		UUserWidget* MenuGameOver = CreateWidget<UUserWidget>(GetWorld(), ClaseMenuGameOver);
		
		if (MenuGameOver)
		{
			MenuGameOver->AddToViewport();

			// 4. Liberamos el ratón para que pueda clickear "Reintentar"
			APlayerController* PC = Cast<APlayerController>(GetController());
			if (PC)
			{
				PC->bShowMouseCursor = true;

				// Forzamos el foco en la UI para que el jugador no siga disparando o rotando la cámara fantasma
				FInputModeUIOnly InputModeData;
				PC->SetInputMode(InputModeData);
			}

			// 5. Pausamos el mundo (opcional, si prefieres que la acción se detenga)
			UGameplayStatics::SetGamePaused(GetWorld(), true);
		}
	}
}

