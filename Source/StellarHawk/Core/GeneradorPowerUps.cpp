// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneradorPowerUps.h"
#include "Math/UnrealMathUtility.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AGeneradorPowerUps::AGeneradorPowerUps()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    CantidadAGenerar = 10;
    LimitesEjeX = FVector2D(0.0f, 20000.0f);
    LimitesEjeY = FVector2D(-20000.0f, 20000.0f);

    static ConstructorHelpers::FClassFinder<APowerUpItem> ClaseCadencia(TEXT("Class'/Script/StellarHawk.CadenciaDisparoItem'"));
    static ConstructorHelpers::FClassFinder<APowerUpItem> ClaseVelocidad(TEXT("Class'/Script/StellarHawk.Velocidad'"));
	static ConstructorHelpers::FClassFinder<APowerUpItem> ClaseEscudo(TEXT("Class'/Script/StellarHawk.Escudo'"));

    // 3. Si las encuentra, las añadimos a la lista que leerá el bucle en el BeginPlay
    if (ClaseCadencia.Succeeded())
    {
        ClasesDePowerUps.Add(ClaseCadencia.Class);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Generador: No se encontró BP_PowerUpCura_C"));
    }

    if (ClaseVelocidad.Succeeded())
    {
        ClasesDePowerUps.Add(ClaseVelocidad.Class);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Generador: No se encontró BP_PowerUpArma_C"));
    }

    if(ClaseEscudo.Succeeded())
    {
        ClasesDePowerUps.Add(ClaseEscudo.Class);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Generador: No se encontró BP_PowerUpEscudo_C"));
	}

}

// Called when the game starts or when spawned
void AGeneradorPowerUps::BeginPlay()
{
	Super::BeginPlay();
	
    if (ClasesDePowerUps.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("GeneradorPowerUps no tiene clases asignadas en su lista."));
        return;
    }

    for (int32 i = 0; i < CantidadAGenerar; i++)
    {
        int32 IndiceAleatorio = FMath::RandRange(0, ClasesDePowerUps.Num() - 1);

        TSubclassOf<APowerUpItem> ClaseSeleccionada = ClasesDePowerUps[IndiceAleatorio];

        if (ClaseSeleccionada)
        {
            float PosicionX = FMath::RandRange(LimitesEjeX.X, LimitesEjeX.Y);
            float PosicionY = FMath::RandRange(LimitesEjeY.X, LimitesEjeY.Y);

            FVector PosicionDeSpawn(PosicionX, PosicionY, 0.0f);

            FActorSpawnParameters SpawnParams;
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

            GetWorld()->SpawnActor<APowerUpItem>(ClaseSeleccionada, PosicionDeSpawn, FRotator::ZeroRotator, SpawnParams);
        }
    }
}

// Called every frame
void AGeneradorPowerUps::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

