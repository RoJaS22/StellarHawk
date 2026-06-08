// Fill out your copyright notice in the Description page of Project Settings.


#include "InterfaceEnemigo.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "EstrategiaEnemigo.h"
#include "EnemigoState.h"
#include "GameManager.h"
#include "PatrullarState.h"
#include "StellarHawkPawn.h"


// Sets default values
AInterfaceEnemigo::AInterfaceEnemigo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MallaEnemigo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaEnemigo"));
	RootComponent = MallaEnemigo;

	VidaMaxima = 100.0f;
	Vida = VidaMaxima;
	Estrategia = nullptr;
}

// Called when the game starts or when spawned
void AInterfaceEnemigo::BeginPlay()
{
	Super::BeginPlay();
	
	UPatrullarState* PatrullarState = NewObject<UPatrullarState>(this);
	CambiarState(PatrullarState);

	GenerarPuntosRuta();
}

void AInterfaceEnemigo::MirarHacia(FVector UbicacionObjetivo, float DeltaTime)
{
	FVector Direccion = (UbicacionObjetivo - GetActorLocation()).GetSafeNormal();
	FRotator RotacionObjetivo = UKismetMathLibrary::MakeRotFromX(Direccion);
	FRotator RotacionSuave = FMath::RInterpTo(GetActorRotation(), RotacionObjetivo, DeltaTime, VelocidadRotacion * 2.0f);

	SetActorRotation(RotacionSuave);
}

void AInterfaceEnemigo::GenerarPuntosRuta()
{
	for (int32 i = 0; i < 10; i++)
	{
		float X = FMath::RandRange(1000.0f, 20000.0f);
		float Y = FMath::RandRange(1000.0f, 20000.0f);
		FVector NuevoPuntoRuta(X, Y, 200);  // Mantiene altura
		PuntosRuta.Add(NuevoPuntoRuta);
	}
}

void AInterfaceEnemigo::CambiarState(UEnemigoState* NuevoState)
{
	if (ActualState)
	{
		ActualState->SalirState(this);
	}

	ActualState = NuevoState;

	if (ActualState)
	{
		ActualState->EntrarState(this);
	}
}

float AInterfaceEnemigo::TakeDamage(float CantidadDanio, FDamageEvent const& EventoDanio, AController* CausanteEvento, AActor* CausanteDanio)
{
	RecibirDanio(CantidadDanio);

	return CantidadDanio;
}

bool AInterfaceEnemigo::VeAlJugador()
{
	APawn* Jugador = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (!Jugador) return false;

	FVector UbicacionInicial = GetActorLocation();
	FVector UbicacionJugador = Jugador->GetActorLocation();
	float DistanciaAlJugador = FVector::Dist(UbicacionInicial, UbicacionJugador);

	if (DistanciaAlJugador > RadioDeteccion)
	{
		return false;
	}

	FVector Adelante = GetActorForwardVector();
	FVector DireccionAlJugador = (UbicacionJugador - UbicacionInicial).GetSafeNormal();
	float ProductoPunto = FVector::DotProduct(Adelante, DireccionAlJugador);

	float Umbral = FMath::Cos(FMath::DegreesToRadians(GradosVision));

	if (ProductoPunto < Umbral)	return false;

	FHitResult ResultadoHit;
	FCollisionQueryParams ParametrosRastro;
	ParametrosRastro.AddIgnoredActor(this);

	FCollisionObjectQueryParams ParametrosObjeto;
	ParametrosObjeto.AddObjectTypesToQuery(ECC_Pawn);
	ParametrosObjeto.AddObjectTypesToQuery(ECC_WorldStatic);
	ParametrosObjeto.AddObjectTypesToQuery(ECC_WorldDynamic);

	bool bHit = GetWorld()->LineTraceSingleByObjectType(
		ResultadoHit,
		UbicacionInicial,
		UbicacionJugador,
		ParametrosObjeto,
		ParametrosRastro
	);

	// --- SECCIÓN DE DEPURACIÓN VISUAL (Opcional) ---
	/*
	// Te dice a que esta golpeando el rayo, si es el jugador o un asteroide
	if (bHit && ResultadoHit.GetActor())
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Golpeó a: %s"), *ResultadoHit.GetActor()->GetName()));
	}
	*/
	// Pinta la línea de verde si ve al jugador, roja si choca con otra cosa (asteroide)
	FColor ColorLinea = (bHit && ResultadoHit.GetActor() == Jugador) ? FColor::Green : FColor::Blue;
	DrawDebugLine(GetWorld(), UbicacionInicial, UbicacionJugador, ColorLinea, false, 0.1f, 0, 2.0f);

	if (bHit && ResultadoHit.GetActor() == Jugador) return true;

	return false;
}

// Called every frame
void AInterfaceEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActualState)
	{
		ActualState->ActualizarState(this, DeltaTime);
	}

	if (Estrategia)
	{
		Estrategia->EjecutarEstrategia(this, DeltaTime);
	}
}

void AInterfaceEnemigo::SetEstrategia(UEstrategiaEnemigo* NuevaEstrategia)
{
	Estrategia = NuevaEstrategia;
}

float AInterfaceEnemigo::GetVida() const
{
	return Vida;
}

float AInterfaceEnemigo::GetVidaMaxima() const
{
	return VidaMaxima;
}

void AInterfaceEnemigo::RecibirDanio(float Cantidad)
{
	Vida -= Cantidad;

	if (Vida <= 0.0f)
	{
		Vida = 0.0f;

		if (AGameManager::GetInstancia())
		{
			AGameManager::GetInstancia()->RegistrarEnemigoDestruido();
		}
	
		Destroy();
	}
}

void AInterfaceEnemigo::Curar(float Cantidad)
{
	Vida += Cantidad;

	if (Vida > VidaMaxima)
	{
		Vida = VidaMaxima;
	}
}