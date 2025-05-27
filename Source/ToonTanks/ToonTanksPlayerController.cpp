// Fill out your copyright notice in the Description page of Project Settings.
#include "ToonTanksPlayerController.h"

#include "GameFramework/Pawn.h"

void AToonTanksPlayerController::SetPlayerEnabledState(bool InputEnabled){
    if (InputEnabled){
        GetPawn()->EnableInput(this); // enable input from keys to action mappings
    }else{
        GetPawn()->DisableInput(this);
    }
    bShowMouseCursor = InputEnabled; // bShowMouseCursor is a field within PlayerController which if true shows Mouse else does not
}
