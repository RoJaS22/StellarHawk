// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneradorAsteroidesMapa.h"
#include "Components/BoxComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Asteroide.h"

// Sets default values
AGeneradorAsteroidesMapa::AGeneradorAsteroidesMapa()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    SpawnVolumen = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolumen"));
    RootComponent = SpawnVolumen;

    // Configuración de las colisiones del volumen (solo sirve de trigger/guía)
    SpawnVolumen->SetCollisionProfileName(TEXT("NoCollision"));

    // Configuración del HISM adjunto al Root
    AsteroideHISM = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("AsteroideHISM"));
    AsteroideHISM->SetupAttachment(RootComponent);

    // Valores iniciales por defecto (puedes cambiarlos en el editor por cada zona)
    CantidadAsteroides = 400;
    MinEscala = 0.4f;
    MaxEscala = 2.5f;

	ClaseAsteroide = AAsteroide::StaticClass();

}

// Called when the game starts or when spawned
void AGeneradorAsteroidesMapa::BeginPlay()
{
	Super::BeginPlay();
	
	GenerarMapa();
}

void AGeneradorAsteroidesMapa::GenerarMapa()
{
    if (!ClaseAsteroide) return;

    GEngine->AddOnScreenDebugMessage(
        -1,             // Clave (-1 crea un nuevo mensaje en cada llamada)
        5.f,            // Tiempo que durará en pantalla (segundos)
        FColor::Yellow, // Color del texto
        TEXT("GeneradorAsteroidesMapa Sirve") // El texto a mostrar (usa siempre TEXT())
    );

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    for (int32 i = 0; i < CantidadAsteroides; ++i)
    {
        float X = FMath::RandRange(-10000.0f, 10000.0f);
        float Y = FMath::RandRange(-10000.0f, 10000.0f);
        FVector UbicacionAleatoria(X, Y, 200.0f);

        FRotator RotacionAleatoria = FRotator(FMath::RandRange(0.f, 360.f), FMath::RandRange(0.f, 360.f), FMath::RandRange(0.f, 360.f));
        float EscalaBruta = FMath::RandRange(MinEscala, MaxEscala);
        FVector EscalaAleatoria = FVector(EscalaBruta);

        // SPAWNEAR EL ACTOR REAL EN EL MUNDO
        AAsteroide* NuevoAsteroide = GetWorld()->SpawnActor<AAsteroide>(ClaseAsteroide, UbicacionAleatoria, RotacionAleatoria, SpawnParams);

        if (NuevoAsteroide)
        {
            NuevoAsteroide->SetActorScale3D(EscalaAleatoria);
            AsteroidesSpawneados.Add(NuevoAsteroide);
        }
    }
}

// Called every frame
void AGeneradorAsteroidesMapa::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

