// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
class UButton;

UCLASS()
class STELLARHAWK_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidget))
    UButton* BotonReintentar;

    UPROPERTY(meta = (BindWidget))
    UButton* BotonMenuPrincipal;

    UFUNCTION()
    void OnReintentarClickeado();

    UFUNCTION()
    void OnMenuPrincipalClickeado();
	
};
