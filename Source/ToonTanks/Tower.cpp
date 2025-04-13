// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // if the tank is within range then rotate the turret to the tank. Distance between Tank and the tower.
    // Make sure the tank pointer is not null before getting the location
    if(Tank){ 
        float Distance = FVector::Dist(Tank->GetActorLocation(), GetActorLocation());

        if(Distance < FireRange){
            RotateTurret(Tank->GetActorLocation());
        }
    }    
}


void ATower::BeginPlay()
{
    Super::BeginPlay();

    // this is using our current world and the player index of 0 for singleplayer to get ahold of the tank pawn
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::ShouldFire, FireRate, true);
}


// callback function passed called by turret to check if it should fire
void ATower::ShouldFire()
{   
    if(Tank){
        float Distance = FVector::Dist(Tank->GetActorLocation(), GetActorLocation());
        if(Distance < FireRange){
            Fire();
        }
    }
}