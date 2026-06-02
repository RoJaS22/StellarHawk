// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "StellarHawkPawn.h" 
#include "PowerUpsDecorator.h"

// Sets default values
APowerUpItem::APowerUpItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Colision = CreateDefaultSubobject<USphereComponent>(TEXT("Esfera"));
    Colision->InitSphereRadius(60.0f);

    // Le decimos que genere eventos de superposición (Overlap)
    Colision->SetCollisionProfileName(TEXT("Superposicion"));
    RootComponent = Colision;

    // 2. Configurar el componente visual
    Malla = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla"));
    Malla->SetupAttachment(RootComponent);
    Malla->SetCollisionEnabled(ECollisionEnabled::NoCollision);   

    // 3. Vincular la función al evento de Overlap
    Colision->OnComponentBeginOverlap.AddDynamic(this, &APowerUpItem::AlSolaparse);

}

void APowerUpItem::AlSolaparse(UPrimitiveComponent* SolapadoComp, AActor* OtroActor, UPrimitiveComponent* OtroComp, int32 IndiceOtroCuerpo, bool bBarrido, const FHitResult& BarridoResultado)
{
    if (OtroActor && OtroActor != this)
    {
        // Intentamos convertir al actor en la nave del jugador
        AStellarHawkPawn* Jugador = Cast<AStellarHawkPawn>(OtroActor);

        // Si el cast funciona (era el jugador) y tenemos un PowerUp asignado
        if (Jugador && PowerUpAplicar)
        {
            GEngine->AddOnScreenDebugMessage(
                -1,             // Clave (-1 crea un nuevo mensaje en cada llamada)
                5.f,            // Tiempo que durará en pantalla (segundos)
                FColor::Yellow, // Color del texto
                TEXT("Funciona") // El texto a mostrar (usa siempre TEXT())
            );
            // ¡Aplicamos el patrón Decorator a las estadísticas del jugador!
            Jugador->AplicarPowerUp(PowerUpAplicar);

            // Opcional: Aquí podrías reproducir un sonido o partículas
            // UGameplayStatics::PlaySoundAtLocation(...)

            // Destruimos la caja del mundo
            Destroy();
        }
    }
}

// Called when the game starts or when spawned
void APowerUpItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerUpItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

