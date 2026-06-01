// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroide.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AAsteroide::AAsteroide()
{
	PrimaryActorTick.bCanEverTick = true;

	Malla = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Malla"));
	RootComponent = Malla;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsteroide(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'")
	);

	if (MeshAsteroide.Succeeded())
	{
		Malla->SetStaticMesh(MeshAsteroide.Object);
	}

	Velocidad = 300.0f;
	Vida = 100.0f;
	DireccionMovimiento = FVector(-1.0f, 0.0f, 0.0f);
}

void AAsteroide::BeginPlay()
{
	Super::BeginPlay();
}

void AAsteroide::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Mover(DeltaTime);
}

void AAsteroide::Mover(float DeltaTime)
{
	FVector NuevaUbicacion = GetActorLocation() + DireccionMovimiento * Velocidad * DeltaTime;
	SetActorLocation(NuevaUbicacion);
}

void AAsteroide::RecibirDanio(float Danio)
{
	Vida -= Danio;

	if (Vida <= 0)
	{
		Destroy();
	}
}

float AAsteroide::TakeDamage(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser
)
{
	RecibirDanio(DamageAmount);

	return DamageAmount;
}