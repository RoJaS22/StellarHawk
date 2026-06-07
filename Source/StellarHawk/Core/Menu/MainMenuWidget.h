// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
class UButton;

UCLASS()
class STELLARHAWK_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UButton* BotonJugar;

    UPROPERTY(meta = (BindWidget))
    UButton* BotonSalir;

    // --- FUNCIONES DE LOS BOTONES ---
    UFUNCTION()
    void OnJugarClickeado();

    UFUNCTION()
    void OnSalirClickeado();
	
};
