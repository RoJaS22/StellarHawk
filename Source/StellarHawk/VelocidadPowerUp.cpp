// Fill out your copyright notice in the Description page of Project Settings.


#include "VelocidadPowerUp.h"

float UVelocidadPowerUp::GetVelocidadMovimiento() const
{
    return Super::GetVelocidadMovimiento() * 1.5f; 
}
