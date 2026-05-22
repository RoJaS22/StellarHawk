// Copyright Epic Games, Inc. All Rights Reserved.

#include "StellarHawkGameMode.h"
#include "StellarHawkPawn.h"

AStellarHawkGameMode::AStellarHawkGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AStellarHawkPawn::StaticClass();
}

