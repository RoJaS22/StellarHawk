// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (BotonJugar)
    {
        BotonJugar->OnClicked.AddDynamic(this, &UMainMenuWidget::OnJugarClickeado);
    }

    if (BotonSalir)
    {
        BotonSalir->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSalirClickeado);
    }
}

void UMainMenuWidget::OnJugarClickeado()
{
    UGameplayStatics::OpenLevel(this, FName("Nivel_1"));
}

void UMainMenuWidget::OnSalirClickeado()
{
    UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}
