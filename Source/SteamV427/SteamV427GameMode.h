// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Public/SteamPlayerController.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SteamV427GameMode.generated.h"

UCLASS(minimalapi)
class ASteamV427GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASteamV427GameMode();

public:
	virtual void Tick(float DeltaSeconds) override;
};



