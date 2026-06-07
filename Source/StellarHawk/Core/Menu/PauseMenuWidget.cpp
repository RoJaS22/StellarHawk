// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UPauseMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (BotonContinuar)
    {
        BotonContinuar->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnContinuarClickeado);
    }

    if (BotonMenuPrincipal)
    {
        BotonMenuPrincipal->OnClicked.AddDynamic(this, &UPauseMenuWidget::OnMenuPrincipalClickeado);
    }
}

void UPauseMenuWidget::OnContinuarClickeado()
{
    UGameplayStatics::SetGamePaused(GetWorld(), false);

    // 2. Ocultamos el ratón y devolvemos el control al juego
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        PC->bShowMouseCursor = false;
        PC->SetInputMode(FInputModeGameOnly());
    }

    // 3. Destruimos este menú de pausa
    RemoveFromParent();
}

void UPauseMenuWidget::OnMenuPrincipalClickeado()
{
    UGameplayStatics::SetGamePaused(GetWorld(), false);

    // Cambia "Map_MainMenu" por el nombre de tu mapa del menú inicial
    UGameplayStatics::OpenLevel(this, FName("MapaMenu"));
}

