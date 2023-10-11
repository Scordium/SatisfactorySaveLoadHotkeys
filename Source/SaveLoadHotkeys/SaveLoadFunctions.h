// 

#pragma once

#include "CoreMinimal.h"
#include "FGGameMode.h"
#include "FGGameState.h"
#include "FGSaveSession.h"
#include "FGSaveSystem.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SaveLoadFunctions.generated.h"

/**
 * 
 */
UCLASS()
class SAVELOADHOTKEYS_API USaveLoadFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static void Save(UObject* WorldContext)
	{
		if(!WorldContext) return;
		
		auto Session = UFGSaveSession::Get(WorldContext);
		Session->Autosave();
	}

	UFUNCTION(BlueprintCallable)
	static void Load(UObject* WorldContext)
	{
		if(!WorldContext) return;
		
		auto SaveSystem = UFGSaveSystem::Get(WorldContext);
		auto Sessions = SaveSystem->NativeEnumerateSaveGames();
		auto SessionName = Cast<AFGGameMode>(WorldContext->GetWorld()->GetAuthGameMode())->GetSaveSessionName();

		FSaveHeader LatestSaveHeader = FSaveHeader();
		for(auto Session : Sessions)
		{
			if(Session.SessionName != SessionName) continue;
			
			if(Session.PlayDurationSeconds > LatestSaveHeader.PlayDurationSeconds) LatestSaveHeader = Session;
		}


		auto Options = TMap<FString, FString>();
		auto Player = UGameplayStatics::GetPlayerController(WorldContext, 0);
		SaveSystem->LoadSaveFile(LatestSaveHeader, Options, Player);
	}

	UFUNCTION(BlueprintPure)
	static double GetSecondsSinceLastSave(UObject* WorldContext)
	{
		auto SaveSystem = UFGSaveSystem::Get(WorldContext);
		auto Sessions = SaveSystem->NativeEnumerateSaveGames();
		auto GameState = Cast<AFGGameState>(UGameplayStatics::GetGameState(WorldContext));
		auto const SessionName = GameState->GetSessionName();

		FSaveHeader LatestSaveHeader = FSaveHeader();
		for(auto Session : Sessions)
		{
			if(Session.SessionName != SessionName) continue;
			
			if(Session.PlayDurationSeconds > LatestSaveHeader.PlayDurationSeconds) LatestSaveHeader = Session;
		}

		return GameState->GetTotalPlayDuration() - LatestSaveHeader.PlayDurationSeconds;
	}
	
};
