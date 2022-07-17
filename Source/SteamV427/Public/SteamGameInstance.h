// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SteamGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class STEAMV427_API USteamGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	USteamGameInstance();
	~USteamGameInstance();

protected:
	IOnlineSubsystem* Subsystem = nullptr;
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	virtual void Init() override;

	virtual void OnCreateSessionComplete(FName SessionName, bool Succeeded);
	virtual void OnFindSessionComplete(bool Succeeded);
	virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION(BlueprintCallable)
	void CreateServer(FString GameName);
	
	UFUNCTION(BlueprintCallable)
	void FindServer();

	UFUNCTION(BlueprintCallable)
	void JoinServer(FString SessionId);

	UFUNCTION(BlueprintCallable)
	void QuitServer();

public:
	UPROPERTY(BlueprintReadOnly)
	TMap<FString, FString> SessionsFoundMap;

	UPROPERTY(BlueprintReadWrite)
	bool DisplaySessionInUI = false;
};
