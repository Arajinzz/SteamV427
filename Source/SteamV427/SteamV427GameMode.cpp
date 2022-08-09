// Copyright Epic Games, Inc. All Rights Reserved.

#include "SteamV427GameMode.h"
#include "SteamV427Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ASteamV427GameMode::ASteamV427GameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = ASteamPlayerController::StaticClass();
}

void ASteamV427GameMode::Tick(float DeltaSeconds)
{
	ASteamPlayerController* PC = Cast<ASteamPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	PC->PlayerPosition = PlayerPawn->GetActorLocation();
	PC->PlayerRotation = PlayerPawn->GetActorRotation();
	GEngine->AddOnScreenDebugMessage(0, 0, FColor::Red, FString::Printf(TEXT("Location: %s"), *PC->PlayerPosition.ToString()));
	GEngine->AddOnScreenDebugMessage(1, 0, FColor::Red, FString::Printf(TEXT("Rotation: %s"), *PC->PlayerRotation.ToString()));
}
