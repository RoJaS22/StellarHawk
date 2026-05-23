// Fill out your copyright notice in the Description page of Project Settings.


#include "Velocidad.h"
#include "VelocidadPowerUp.h" // Tu clase decoradora concreta
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h" 

AVelocidad::AVelocidad()
{
    PowerUpAplicar = UVelocidadPowerUp::StaticClass();

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

    if (MallaAsset.Succeeded())
    {
        Malla->SetStaticMesh(MallaAsset.Object);
    }
}
