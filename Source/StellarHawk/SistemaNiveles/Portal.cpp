// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "StellarHawkPawn.h"

// Sets default values
APortal::APortal()
{
    PrimaryActorTick.bCanEverTick = false;
    bEstaActivo = false;

    // 1. Configuramos lo visual
    PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
    RootComponent = PortalMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaAsset(TEXT("StaticMesh'/Game/MallaNave/uploads_files_4492463_Portal.uploads_files_4492463_Portal'"));
    if(MallaAsset.Succeeded())
    {
        PortalMesh->SetStaticMesh(MallaAsset.Object);
        //PortalMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("Material'/Game/MallaNave/MaterialPortalActivo.MaterialPortalActivo'"));
    if(MaterialAsset.Succeeded())
    {
        NuevoMaterial = MaterialAsset.Object;
	}
    
    // 2. Configuramos la caja de detección
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);

    // IMPORTANTE: El portal nace DESACTIVADO (sin colisión)
    TriggerBox->SetBoxExtent(FVector(500.0f, 500.0f, 100.0f));
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);
}

void APortal::ActivarPortal()
{
    bEstaActivo = true;

    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    GEngine->AddOnScreenDebugMessage(
        -1,             // Clave (-1 crea un nuevo mensaje en cada llamada)
        5.f,            // Tiempo que durará en pantalla (segundos)
        FColor::Black, // Color del texto
        TEXT("Esta activo el portal") // El texto a mostrar (usa siempre TEXT())
    );

	// Aquí podríamos agregar efectos visuales o sonoros para indicar que el portal se ha activado
    if (PortalMesh && NuevoMaterial)
    {
        PortalMesh->SetMaterial(1, NuevoMaterial);
    }
}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (bEstaActivo && OtherActor && OtherActor != this)
    {
        AStellarHawkPawn* Jugador = Cast<AStellarHawkPawn>(OtherActor);
        if (Jugador)
        {
            GEngine->AddOnScreenDebugMessage(
                -1,             // Clave (-1 crea un nuevo mensaje en cada llamada)
                5.f,            // Tiempo que durará en pantalla (segundos)
                FColor::Black, // Color del texto
                TEXT("Funca") // El texto a mostrar (usa siempre TEXT())
            );
            if (!NombreSiguienteNivel.IsNone())
            {
                GEngine->AddOnScreenDebugMessage(
                    -1,             // Clave (-1 crea un nuevo mensaje en cada llamada)
                    5.f,            // Tiempo que durará en pantalla (segundos)
                    FColor::Black, // Color del texto
                    TEXT("Cambiio nivel") // El texto a mostrar (usa siempre TEXT())
                );
                UGameplayStatics::OpenLevel(GetWorld(), NombreSiguienteNivel);
            }
        }
    }
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

