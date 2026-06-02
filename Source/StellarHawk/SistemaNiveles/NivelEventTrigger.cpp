// Fill out your copyright notice in the Description page of Project Settings.


#include "NivelEventTrigger.h"
#include "Components/BoxComponent.h"

// Sets default values
ANivelEventTrigger::ANivelEventTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    bHaSidoActivado = false;

    // Configuración del volumen de colisión
    TriggerVolumen = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
    RootComponent = TriggerVolumen;

    // Configurar colisiones para que actúe como un Query Trigger (no físico)
    TriggerVolumen->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    TriggerVolumen->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerVolumen->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

    // IMPORTANTE: Asegúrate de que el canal coincida con el de tu tipo de Nave (ej: Pawn)
    TriggerVolumen->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void ANivelEventTrigger::BeginPlay()
{
	Super::BeginPlay();

    TriggerVolumen->OnComponentBeginOverlap.AddDynamic(this, &ANivelEventTrigger::OnVolumeOverlapBegin);
}

void ANivelEventTrigger::OnVolumeOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Si ya se activó o no hay enemigos configurados, ignoramos
    if (bHaSidoActivado || EnemigosSpawnear.Num() == 0) return;

    if (OtherActor && OtherActor != this)
    {
        // TODO: Verifica aquí si el OtherActor es efectivamente la nave del jugador
        // Ej: if (OtherActor->IsA(AMyPlayerShip::StaticClass()))

        bHaSidoActivado = true; // Bloqueamos futuras ejecuciones

        // Obtenemos el GameMode para delegar el Spawn
        if (UWorld* World = GetWorld())
        {
            if (AGameModeBase* CurrentGameMode = World->GetAuthGameMode())
            {
                // Aquí haces el Cast a tu GameMode personalizado y le pasas la data:
                // ATuGameMode* SpaceGM = Cast<ATuGameMode>(CurrentGameMode);
                // if (SpaceGM) { SpaceGM->RequestWaveSpawn(EnemiesToSpawn, GetActorLocation()); }

                UE_LOG(LogTemp, Log, TEXT("ANivelEventTrigger: Jugador detectado. Enviando oleada de %d enemigos al GameMode."), EnemigosSpawnear.Num());
            }
        }

        // Opcional: Si el trigger no hace nada más, puedes destruirlo para liberar memoria
        // Destroy();
    }
}

// Called every frame
void ANivelEventTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

