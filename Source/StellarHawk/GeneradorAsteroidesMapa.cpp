// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneradorAsteroidesMapa.h"
#include "Components/BoxComponent.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

}

// Called when the game starts or when spawned
void AGeneradorAsteroidesMapa::BeginPlay()
{
	Super::BeginPlay();
	
	GenerarMapa();
}

void AGeneradorAsteroidesMapa::GenerarMapa()
{
    if (!AsteroideHISM || !SpawnVolumen) return;

    // Validación crítica: Si el HISM no tiene un mesh asignado, crasheará o no hará nada
    if (!AsteroideHISM->GetStaticMesh())
    {
        UE_LOG(LogTemp, Warning, TEXT("AAsteroidFieldZone [%s]: No has asignado un Static Mesh al componente HISM."), *GetName());
        return;
    }

    FVector BoxExtent = SpawnVolumen->GetScaledBoxExtent();
    FVector BoxOrigin = SpawnVolumen->GetComponentLocation();

    for (int32 i = 0; i < CantidadAsteroides; ++i)
    {
        // 1. Obtener un punto completamente aleatorio dentro de la caja de colisión
        FVector UbicacionAleatoria = FMath::VRand() * 10000.0f;

        // 2. RESTRICCIÓN 2.5D: Forzamos que la posición en Y sea exactamente la del plano de juego (ej. 0.0)
        UbicacionAleatoria.Z = 0.0f;

        // 3. Rotación tridimensional completamente aleatoria para que no se note la repetición del mismo mesh
        FRotator RotacionAleatoria = FRotator(
            FMath::RandRange(0.f, 360.f), // Pitch
            FMath::RandRange(0.f, 360.f), // Yaw
            FMath::RandRange(0.f, 360.f)  // Roll
        );

        // 4. Escala uniforme aleatoria para mantener las proporciones del asteroide
        float RawScale = FMath::RandRange(MinEscala, MaxEscala);
        FVector RandomScale = FVector(RawScale);

        // 5. Construir la transformación final e instanciar
        FTransform TransformacionInstancia(RotacionAleatoria, UbicacionAleatoria, RandomScale);
        AsteroideHISM->AddInstance(TransformacionInstancia);
    }
}

// Called every frame
void AGeneradorAsteroidesMapa::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

