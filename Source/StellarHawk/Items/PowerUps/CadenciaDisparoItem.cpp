// Fill out your copyright notice in the Description page of Project Settings.


#include "CadenciaDisparoItem.h"
#include "CadenciaDisparoPowerUp.h" 
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h" 

ACadenciaDisparoItem::ACadenciaDisparoItem()
{
    PowerUpAplicar = UCadenciaDisparoPowerUp::StaticClass();

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("Material'/Game/MaterialesItems/MaterialCadencia.MaterialCadencia'"));

    if (MallaAsset.Succeeded())
    {
        Malla->SetStaticMesh(MallaAsset.Object);
		Malla->SetWorldScale3D(FVector(6.0f)); // Escala más pequeña para diferenciarlo
		Malla->SetMaterial(0, MaterialAsset.Object);
    }
}
