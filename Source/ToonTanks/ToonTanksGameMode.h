// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void ActorDied(AActor* DeadActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// function that is defined in Blueprints for adding frontend widget
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	// function that is defined in Blueprints for when game is over
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

private:
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController; // pointer to custom player controller rather than having it located on the Tank

	float StartDelay = 3.f; // wait 3 seconds before enabling input
	void HandleGameStart();

	int32 numTowers = 0;
	int32 GetTargetTowerCount();
};
