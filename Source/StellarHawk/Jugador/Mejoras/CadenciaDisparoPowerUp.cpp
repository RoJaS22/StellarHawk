// Fill out your copyright notice in the Description page of Project Settings.


#include "CadenciaDisparoPowerUp.h"

float UCadenciaDisparoPowerUp::GetCadenciaDisparo() const
{
	return Super::GetCadenciaDisparo() * 0.5f;
}
