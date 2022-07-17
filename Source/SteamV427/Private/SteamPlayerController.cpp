// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamPlayerController.h"

bool ASteamPlayerController::Server_SendChatMessage_Validate(const FString& ChatMessage) {
	return true; 
}

void ASteamPlayerController::Server_SendChatMessage_Implementation(const FString& ChatMessage)
{
	UE_LOG(LogTemp, Warning, TEXT("Sending a Chat message: %s"), *ChatMessage);
	// Iterate over all clients in the map and send the message to them
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		if (ASteamPlayerController* const PC = Cast<ASteamPlayerController>(*Iterator))
		{
			PC->Client_ReceiveChatMessage(ChatMessage);
		}
	}
}

bool ASteamPlayerController::Client_ReceiveChatMessage_Validate(const FString& ChatMessage)
{
	return true;
}

void ASteamPlayerController::Client_ReceiveChatMessage_Implementation(const FString& ChatMessage)
{
	m_OnChatMessageReceived.Broadcast(ChatMessage);
	UE_LOG(LogTemp, Warning, TEXT("Message Received: %s"), *ChatMessage);
}
