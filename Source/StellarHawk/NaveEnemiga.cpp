// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveEnemiga.h"
#include "EnemigoState.h"
#include "PatrullarState.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "StellarHawkProjectile.h"



// Sets default values
ANaveEnemiga::ANaveEnemiga()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MallaNaveEnemiga = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaNaveEnemiga"));
	RootComponent = MallaNaveEnemiga;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Trim.Shape_Trim'"));

	if(MallaAsset.Succeeded())
	{
		MallaNaveEnemiga->SetStaticMesh(MallaAsset.Object);
	}

	// Si no dispara comente esta línea, compile, descomente y vuelva a compilar
	Proyectil = AStellarHawkProjectile::StaticClass();

	// Stats Nave Enemiga
	Vida = 100.0f;
}

bool ANaveEnemiga::VeAlJugador()
{
	APawn* Jugador = UGameplayStatics::GetPlayerPawn(this, 0);

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

// Called when the game starts or when spawned
void ANaveEnemiga::BeginPlay()
{
	Super::BeginPlay();

	FVector Punto1 = GetActorLocation() + FVector(0, 0, 0);
	FVector Punto2 = GetActorLocation() + FVector(1000, 0, 0);
	FVector Punto3 = GetActorLocation() + FVector(1000, 1000, 0);
	PuntosRuta.Add(Punto1);
	PuntosRuta.Add(Punto2);
	PuntosRuta.Add(Punto3);
	
	UPatrullarState* PatrullarState = NewObject<UPatrullarState>(this);
	CambiarState(PatrullarState);
}

void ANaveEnemiga::Atacar(float DeltaTime)
{
	TiempoDesdeUltimoDisparo += DeltaTime;

	if (TiempoDesdeUltimoDisparo >= CadenciaDisparo && Proyectil)
	{
		TiempoDesdeUltimoDisparo -= CadenciaDisparo;

		FVector UbicacionSpawn = GetActorLocation() + (GetActorForwardVector() * 30.0f);
		FRotator RotacionSpawn = GetActorRotation();

		FActorSpawnParameters ParametrosSpawn;
		ParametrosSpawn.Owner = this;
		ParametrosSpawn.Instigator = GetInstigator();

		ParametrosSpawn.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(Proyectil, UbicacionSpawn, RotacionSpawn, ParametrosSpawn);
	}
}

void ANaveEnemiga::CambiarState(UEnemigoState* NuevoState)
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

float ANaveEnemiga::TakeDamage(float CantidadDanio, FDamageEvent const& EventoDanio, AController* CausanteEvento, AActor* CausanteDanio)
{
	Vida -= CantidadDanio;

	if (Vida <= 0.0f)
	{
		Destroy();
	}

	return CantidadDanio;
}

// Called every frame
void ANaveEnemiga::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActualState)
	{
		ActualState->ActualizarState(this, DeltaTime);
	}
}

