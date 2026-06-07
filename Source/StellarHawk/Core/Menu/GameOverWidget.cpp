// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameOverWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (BotonReintentar)
    {
        BotonReintentar->OnClicked.AddDynamic(this, &UGameOverWidget::OnReintentarClickeado);
    }

    if (BotonMenuPrincipal)
    {
        BotonMenuPrincipal->OnClicked.AddDynamic(this, &UGameOverWidget::OnMenuPrincipalClickeado);
    }
}

void UGameOverWidget::OnReintentarClickeado()
{
    UGameplayStatics::SetGamePaused(GetWorld(), false);

    // TRUCO AVANZADO: Obtenemos el nombre del mapa actual dinámicamente
    FString NombreNivelActual = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);

    UGameplayStatics::OpenLevel(this, FName(*NombreNivelActual));
}

void UGameOverWidget::OnMenuPrincipalClickeado()
{
    UGameplayStatics::SetGamePaused(GetWorld(), false);

    // Cambiamos al mapa de tu menú inicial
    UGameplayStatics::OpenLevel(this, FName("MapaMenu"));
}