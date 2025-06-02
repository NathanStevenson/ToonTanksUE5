// Fill out your copyright notice in the Description page of Project Settings.
#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksPlayerController.h"
#include "TimerManager.h"

#include "Tank.h"
#include "Tower.h"

// call ActorDied on the correct type -> need to cast it because DeadActor is a type of AActor which does not define HandleDestruction()
void AToonTanksGameMode::ActorDied(AActor* DeadActor){
    // if actor is a Tank then disable the input when the actor dies
    if(DeadActor == Tank && ToonTanksPlayerController){
        Tank->HandleDestruction();
        ToonTanksPlayerController->SetPlayerEnabledState(false);
        // if tank died lost game
        GameOver(false);
    }
    else if (ATower* DeadTower = Cast<ATower>(DeadActor)){
        DeadTower->HandleDestruction();
        // if tower dead decr variable
        numTowers--;
        if (numTowers == 0){ 
            GameOver(true); // game has been won
        }
    }
}

void AToonTanksGameMode::BeginPlay(){
    Super::BeginPlay();
    HandleGameStart();
}

// start game; getPlayerPawn and getPlayerController; disable controller; wait N seconds, enable controller again
void AToonTanksGameMode::HandleGameStart(){
    // this is using our current world and the player index of 0 for singleplayer to get ahold of the tank pawn
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    // set tower count for current world
    numTowers = GetTargetTowerCount();
    // call Blueprint function to add the widget to the viewport - triggers BP event
    StartGame();
    // gets the player controller for this gameplay + disable input
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0)); // must be cast from PlayerController to ToonTanks PC
    ToonTanksPlayerController->SetPlayerEnabledState(false);
    // disable, wait, re-enable
    if (ToonTanksPlayerController){
        FTimerDelegate InputDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);
        FTimerHandle PlayerEnableTimerHandle;
        GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, InputDelegate, StartDelay, false);
    }
}

// helper function called at the start of the game which will dynamically count all actors of type tower
int32 AToonTanksGameMode::GetTargetTowerCount() {
    TArray<AActor*> Towers; // TArray out value; will store all tower actor pointers
    // get ATower UClass from blueprints via StaticClass
    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
    return Towers.Num();
}