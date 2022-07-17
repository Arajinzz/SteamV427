// Copyright Epic Games, Inc. All Rights Reserved.

#include "SteamV427GameMode.h"
#include "SteamV427Character.h"
#include "UObject/ConstructorHelpers.h"

ASteamV427GameMode::ASteamV427GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = ASteamPlayerController::StaticClass();
}
