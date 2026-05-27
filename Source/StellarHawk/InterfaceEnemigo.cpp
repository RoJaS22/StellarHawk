// Fill out your copyright notice in the Description page of Project Settings.


#include "InterfaceEnemigo.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "EnemigoState.h"
#include "PatrullarState.h"
#include "StellarHawkPawn.h"

// Sets default values
AInterfaceEnemigo::AInterfaceEnemigo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MallaEnemigo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaEnemigo"));
	RootComponent = MallaEnemigo;
}

// Called when the game starts or when spawned
void AInterfaceEnemigo::BeginPlay()
{
	Super::BeginPlay();
	
	UPatrullarState* PatrullarState = NewObject<UPatrullarState>(this);
	CambiarState(PatrullarState);
}

void AInterfaceEnemigo::MirarHacia(FVector UbicacionObjetivo, float DeltaTime)
{
	FVector Direccion = (UbicacionObjetivo - GetActorLocation()).GetSafeNormal();
	FRotator RotacionObjetivo = UKismetMathLibrary::MakeRotFromX(Direccion);
	FRotator RotacionSuave = FMath::RInterpTo(GetActorRotation(), RotacionObjetivo, DeltaTime, VelocidadRotacion * 2.0f);

	SetActorRotation(RotacionSuave);
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
	Vida -= CantidadDanio;

	if (Vida <= 0.0f)
	{
		Destroy();
	}

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
}