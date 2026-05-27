// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerEnemigos.h"
#include "CreadorFactory.h"
#include "TimerManager.h"
#include "Components/SceneComponent.h"

// Sets default values
ASpawnerEnemigos::ASpawnerEnemigos()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    RootComponent = SceneRoot;

}

// Called when the game starts or when spawned
void ASpawnerEnemigos::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawnerEnemigos::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnerEnemigos::SpawnEnemigo()
{
    if (FabricaEnemigo)
    {
        FTransform SpawnTransformacion = GetActorTransform();

        int32 NivelEnemigo = 1;

        FabricaEnemigo->SpawnearEnemigo(GetWorld(), SpawnTransformacion, NivelEnemigo);
    }
}

void ASpawnerEnemigos::IniciarSpawner(TSubclassOf<class UCreadorFactory> TipoDeFabrica)
{
    if (TipoDeFabrica)
    {
        FabricaEnemigo = NewObject<UCreadorFactory>(this, TipoDeFabrica);

        GetWorld()->GetTimerManager().SetTimer(
            SpawnTimer,
            this,
            &ASpawnerEnemigos::SpawnEnemigo,
            5.0f,
            true
        );

        GEngine->AddOnScreenDebugMessage(
            -1,             // Clave (-1 crea un nuevo mensaje en cada llamada)
            5.f,            // Tiempo que durará en pantalla (segundos)
            FColor::Yellow, // Color del texto
            TEXT("Inicia Spawner") // El texto a mostrar (usa siempre TEXT())
        );
    }
}

