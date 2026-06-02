// Fill out your copyright notice in the Description page of Project Settings.


#include "NivelManager.h"
#include "EnemigoBaseFactory.h"

// Sets default values
ANivelManager::ANivelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ANivelManager::ProcessWaveTrigger(const TArray<FEnemigoSpawnRequest>& EnemiesToSpawn, FVector TriggerLocation)
{
    for (const FEnemigoSpawnRequest& Request : EnemiesToSpawn)
    {
        // 1. Buscamos si existe una fábrica instanciada para este Tipo de Enemigo
        UCreadorFactory** FactoriaEncontrada = FactoriasInstanciadas.Find(Request.IDTipoEnemigo);

        if (FactoriaEncontrada && *FactoriaEncontrada)
        {
            // 2. Calculamos la posición y la blindamos en Y=0
            FVector FinalSpawnLocation = TriggerLocation + Request.SpawnOffset;
            FinalSpawnLocation.Y = 0.0f;

            // 3. Preparamos el FTransform (rotación 0, ubicación calculada, escala 1)
            FTransform SpawnTransformacion(FRotator::ZeroRotator, FinalSpawnLocation, FVector(1.0f));

            // 4. ¡Llamamos a tu función exacta!
            (*FactoriaEncontrada)->CrearEnemigo(GetWorld(), SpawnTransformacion);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("ANivelManager: No se encontró una fábrica instanciada para el enemigo tipo [%s]"), *Request.IDTipoEnemigo.ToString());
        }
    }
}

// Called when the game starts or when spawned
void ANivelManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANivelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

