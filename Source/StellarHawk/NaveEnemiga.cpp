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


	Proyectil = AStellarHawkProjectile::StaticClass();
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

	// Convertimos nuestros grados tolerados a radianes y luego calculamos su coseno
	float Umbral = FMath::Cos(FMath::DegreesToRadians(GradosVision));

	// Si el producto punto es menor que nuestro umbral, el jugador está fuera del cono
	if (ProductoPunto < Umbral)	return false;

	FHitResult ResultadoHit;
	FCollisionQueryParams ParametrosRastro;
	ParametrosRastro.AddIgnoredActor(this);

	// Definimos exactamente con qué tipos de objetos queremos chocar
	FCollisionObjectQueryParams ParametrosObjeto;
	ParametrosObjeto.AddObjectTypesToQuery(ECC_Pawn);        // 1. Queremos chocar con el Jugador
	ParametrosObjeto.AddObjectTypesToQuery(ECC_WorldStatic); // 2. Queremos chocar con Asteroides/Paredes
	ParametrosObjeto.AddObjectTypesToQuery(ECC_WorldDynamic);

	// 3. Disparar el Raycast usando el canal de visibilidad por defecto
	bool bHit = GetWorld()->LineTraceSingleByObjectType(
		ResultadoHit,
		UbicacionInicial,
		UbicacionJugador,
		ParametrosObjeto, 
		ParametrosRastro
	);

	// --- SECCIÓN DE DEPURACIÓN VISUAL (Opcional) ---
	// Pinta la línea de verde si ve al jugador, roja si choca con otra cosa (asteroide)
	// Borra o comenta esto cuando el juego esté listo
	FColor ColorLinea = (bHit && ResultadoHit.GetActor() == Jugador) ? FColor::Green : FColor::Blue;
	DrawDebugLine(GetWorld(), UbicacionInicial, UbicacionJugador, ColorLinea, false, 0.1f, 0, 2.0f);
	// ----------------------------------------------

	// 4. Evaluar el impacto
	if (bHit && ResultadoHit.GetActor() == Jugador) return true;
		// Si el rayo chocó con algo, verificamos si ese actor es el jugador

	// Si llegamos aquí, el rayo chocó con un asteroide o el jugador no estaba en el impacto
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
/*
void ANaveEnemiga::Disparar(float DeltaTime)
{
	TiempoDesdeUltimoDisparo += DeltaTime;

	if (true)
	{
		// Restamos la cadencia en lugar de volver a 0 para mantener la precisión matemática
		TiempoDesdeUltimoDisparo -= CadenciaDisparo;

		// Calculamos la ubicación (Idealmente, en el futuro deberías usar un "Socket" del modelo 3D)
		FVector UbicacionSpawn = GetActorLocation() + (GetActorForwardVector() * 100.0f); // Ajustado a 100 según tu comentario
		FRotator RotacionSpawn = GetActorRotation();

		// Configuramos los parámetros de instanciación
		FActorSpawnParameters ParametrosSpawn;
		ParametrosSpawn.Owner = this;      // El dueño es este enemigo
		ParametrosSpawn.Instigator = GetInstigator(); // El instigador (quién causará el daño)

		// Forzamos que el proyectil aparezca siempre, aunque esté tocando algo
		ParametrosSpawn.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// Spawneamos el proyectil pasándole los parámetros
		GetWorld()->SpawnActor<AActor>(Proyectil, UbicacionSpawn, RotacionSpawn, ParametrosSpawn);
	}
}
*/
// Called every frame
void ANaveEnemiga::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActualState)
	{
		ActualState->ActualizarState(this, DeltaTime);
	}

}

