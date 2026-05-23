// Fill out your copyright notice in the Description page of Project Settings.


#include "Escudo.h"
#include "EscudoPowerUp.h" // Tu clase decoradora concreta
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h" // Necesario para cargar assets

AEscudo::AEscudo()
{
	PowerUpAplicar = UEscudoPowerUp::StaticClass();
	
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MallaAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

    if (MallaAsset.Succeeded())
    {
        Malla->SetStaticMesh(MallaAsset.Object);
    }

    // --- 3. CARGAR UN MATERIAL (Opcional pero recomendado) ---
    // Aquí puedes cargar un material básico del motor para darle color (ej. un material verde brillante).
    // Si ya tienes un material creado, solo copia su referencia en el editor.
    
    //static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

    //if (MaterialAsset.Succeeded())
    //{
    //    Malla->SetMaterial(0, MaterialAsset.Object);
    //}
}
