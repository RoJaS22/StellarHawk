// Fill out your copyright notice in the Description page of Project Settings.


#include "NivelManager.h"
#include "NivelEventTrigger.h"
#include "CreadorFactory.h"
#include "Kismet/GameplayStatics.h"
#include "NivelDataAsset.h"

// Sets default values
ANivelManager::ANivelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void ANivelManager::BeginPlay()
{
	Super::BeginPlay();
	
    if (!DatosDelNivel)
    {
        UE_LOG(LogTemp, Error, TEXT("NivelManager no tiene un Data Asset asignado."));
        return;
    }

    TArray<AActor*> TriggersEnElMundo;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANivelEventTrigger::StaticClass(), TriggersEnElMundo);

    for (AActor* ActorEncontrado : TriggersEnElMundo)
    {
        ANivelEventTrigger* Trigger = Cast<ANivelEventTrigger>(ActorEncontrado);
        if (Trigger)
        {
            Trigger->OnTriggerActivated.AddUObject(this, &ANivelManager::ManejarActivacionTrigger);
        }
    }
}

void ANivelManager::ManejarActivacionTrigger(FName TriggerID, const TArray<FTransform>& PuntosDeSpawn)
{
    if (DatosDelNivel && DatosDelNivel->DatosDeOleadas.Contains(TriggerID))
    {
        FTriggerSpawnData DatosDeLaZona = DatosDelNivel->DatosDeOleadas[TriggerID];

        for (const FEnemySpawnInfo& Info : DatosDeLaZona.ListaDeEnemigos)
        {
            if (Info.ClaseDeFabrica)
            {
                // Instanciamos la fábrica específica
                UCreadorFactory* Fabrica = NewObject<UCreadorFactory>(this, Info.ClaseDeFabrica);

                for (int32 i = 0; i < Info.Cantidad; i++)
                {
                    FTransform TransformacionFinal = FTransform::Identity;

                    if (PuntosDeSpawn.Num() > 0)
                    {
                        int32 IndicePunto = i % PuntosDeSpawn.Num();
                        TransformacionFinal = PuntosDeSpawn[IndicePunto];
                    }

                    Fabrica->SpawnearEnemigo(GetWorld(), TransformacionFinal, 1);
                }
            }
        }
    }
}


