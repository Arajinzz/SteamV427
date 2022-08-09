// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SteamPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChatMessageReceived, const FString&, ChatMessage);

/**
 * 
 */
UCLASS()
class STEAMV427_API ASteamPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation)
	void Server_SendChatMessage(const FString& ChatMessage);
	bool Server_SendChatMessage_Validate(const FString& ChatMessage);
	void Server_SendChatMessage_Implementation(const FString& ChatMessage);

	UFUNCTION(Client, Reliable)
	void Client_ReceiveChatMessage(const FString& ChatMessage);
	bool Client_ReceiveChatMessage_Validate(const FString& ChatMessage);
	void Client_ReceiveChatMessage_Implementation(const FString& ChatMessage);

	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnChatMessageReceived"))
	FOnChatMessageReceived m_OnChatMessageReceived;

public:
	FVector PlayerPosition = FVector(0.0f);
	FRotator PlayerRotation = FRotator(0.0f);

};
