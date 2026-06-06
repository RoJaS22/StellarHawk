// Fill out your copyright notice in the Description page of Project Settings.


#include "NivelEventTrigger.h"
#include "Components/BoxComponent.h"
#include "StellarHawkPawn.h"

// Sets default values
ANivelEventTrigger::ANivelEventTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    bYaActivado = false;

    // Configuración del volumen de colisión
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;

	//Configuraciones del TriggerBox
    TriggerBox->SetBoxExtent(FVector(500.0f, 500.0f, 100.0f));
    TriggerBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ANivelEventTrigger::OnOverlapBegin);
}

void ANivelEventTrigger::BeginPlay()
{
    Super::BeginPlay();

    int32 CantidadDePuntos = 10;
    float Separacion = 5000.0f;

    // Calculamos el centro para que la formación quede centrada respecto al Trigger
    float OffsetInicialY = -((CantidadDePuntos - 1) * Separacion) / 2.0f;

    for (int32 i = 0; i < CantidadDePuntos; i++)
    {
        FVector UbicacionCalculada = GetActorLocation();

        UbicacionCalculada.X += 20000.0f;

        UbicacionCalculada.Y += (OffsetInicialY + (i * Separacion));

        FTransform NuevoTransform(FRotator::ZeroRotator, UbicacionCalculada);
        TransformacionesDeSpawn.Add(NuevoTransform);
    }
}

void ANivelEventTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (bYaActivado || !OtherActor || OtherActor == this) return;

    AStellarHawkPawn* Jugador = Cast<AStellarHawkPawn>(OtherActor);

    if (Jugador)
    {
        bYaActivado = true;

        OnTriggerActivated.Broadcast(TriggerID, TransformacionesDeSpawn);

        TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

        GEngine->AddOnScreenDebugMessage(
            -1,             // Clave (-1 crea un nuevo mensaje en cada llamada)
            5.f,            // Tiempo que durará en pantalla (segundos)
            FColor::Yellow, // Color del texto
            TEXT("Eureka") // El texto a mostrar (usa siempre TEXT())
        );
    }
}


