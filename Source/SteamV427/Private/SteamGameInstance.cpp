// Fill out your copyright notice in the Description page of Project Settings.


#include "SteamGameInstance.h"

USteamGameInstance::USteamGameInstance() {

}

USteamGameInstance::~USteamGameInstance() {
	if (SessionInterface.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("SESSION DESTROYED"));
		SessionInterface->DestroySession(NAME_GameSession);
	}
}

void USteamGameInstance::Init()
{
	Super::Init();
	
	Subsystem = IOnlineSubsystem::Get();

	if (Subsystem) {
		SessionInterface = Subsystem->GetSessionInterface();
		
		if (SessionInterface.IsValid()) {
			// Set delegates
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(
				this, &USteamGameInstance::OnCreateSessionComplete
			);

			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(
				this, &USteamGameInstance::OnFindSessionComplete
			);

			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(
				this, &USteamGameInstance::OnJoinSessionComplete
			);
		}
	}
	
}

void USteamGameInstance::OnCreateSessionComplete(FName SessionName, bool Succeeded)
{
	if (Succeeded) {
		GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	}
}

void USteamGameInstance::OnFindSessionComplete(bool Succeeded)
{
	if (Succeeded) {
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
		if (SearchResults.Num()) {
			for (auto SessionRes : SearchResults) {
				FString GameName;
				SessionRes.Session.SessionSettings.Get("GAMENAME", GameName);
				SessionsFoundMap.Add(
					SessionRes.GetSessionIdStr(),
					GameName
				);
			}
		}
		DisplaySessionInUI = true;
	}
}

void USteamGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (APlayerController* PController = GetWorld()->GetFirstPlayerController()) {
		FString JoinAddress = "";
		SessionInterface->GetResolvedConnectString(SessionName, JoinAddress);
		UE_LOG(LogTemp, Warning, TEXT("JoinAddress is : %s"), *JoinAddress);

		if (JoinAddress != "") {
			PController->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);
		}
	}
}

void USteamGameInstance::CreateServer(FString GameName)
{
	UE_LOG(LogTemp, Warning, TEXT("Create Server: %s"), *Subsystem->GetSubsystemName().ToString());
	FOnlineSessionSettings SessionSettings;

	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = (Subsystem->GetSubsystemName() == "NULL");
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.NumPublicConnections = 5;
	SessionSettings.bUseLobbiesIfAvailable = true;
	SessionSettings.bAllowJoinViaPresence = true;
	SessionSettings.bAllowInvites = true;
	SessionSettings.bAllowJoinViaPresenceFriendsOnly = false;
	SessionSettings.bAntiCheatProtected = false;
	SessionSettings.bUsesStats = false;

	FOnlineSessionSetting ExtraSetting;
	ExtraSetting.Data = GameName;
	//	ViaOnlineServiceAndPing
	ExtraSetting.AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineService;
	SessionSettings.Settings.Add("GAMENAME", ExtraSetting);

	SessionInterface->CreateSession(0, NAME_GameSession, SessionSettings);
}

void USteamGameInstance::FindServer()
{
	DisplaySessionInUI = false;
	SessionsFoundMap.Reset();

	SessionSearch = MakeShareable(new FOnlineSessionSearch());

	SessionSearch->bIsLanQuery = (Subsystem->GetSubsystemName() == "NULL");
	SessionSearch->MaxSearchResults = 10000;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
	
	//SessionSearch->QuerySettings.Set(FName("GAMENAME"), FString("This is my game name"), EOnlineComparisonOp::Equals);
	//SessionSearch->QuerySettings.Set("SEARCH_KEYWORDS", FString::FString("SteamExpirement Session"), EOnlineComparisonOp::Equals);

	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void USteamGameInstance::JoinServer(FString SessionId)
{
	UE_LOG(LogTemp, Warning, TEXT("Session ID to Join : %s"), *SessionId);
	FOnlineSessionSearchResult* Result = nullptr;
	for (auto Session : SessionSearch->SearchResults) {
		if (SessionId.Equals(Session.GetSessionIdStr())) {
			Result = &Session;
			break;
		}
	}

	if (!Result) {
		UE_LOG(LogTemp, Warning, TEXT("Unable to Join Session"));
		return;
	}

	const ULocalPlayer* localPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	SessionInterface->JoinSession(
		*localPlayer->GetPreferredUniqueNetId(), NAME_GameSession, *Result);
}

void USteamGameInstance::QuitServer()
{
	if (!SessionInterface.IsValid()) {
		return;
	}

	if (!SessionInterface->DestroySession(NAME_GameSession))
	{
		UE_LOG(LogTemp, Warning, TEXT("Session Successfully destroyed"));
	}

}
