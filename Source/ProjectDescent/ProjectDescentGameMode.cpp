// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProjectDescentGameMode.h"
#include "ProjectDescentPlayerController.h"
#include "ProjectDescentCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectDescentGameMode::AProjectDescentGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AProjectDescentPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}