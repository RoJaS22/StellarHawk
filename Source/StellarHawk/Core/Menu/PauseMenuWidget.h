// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

/**
 * 
 */
class UButton;

UCLASS()
class STELLARHAWK_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UButton* BotonContinuar;

    UPROPERTY(meta = (BindWidget))
    UButton* BotonMenuPrincipal;

    UFUNCTION()
    void OnContinuarClickeado();

    UFUNCTION()
    void OnMenuPrincipalClickeado();
	
};
