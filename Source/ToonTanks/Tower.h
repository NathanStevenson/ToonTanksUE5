// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	// cleans up the pawn when it is dead
	void HandleDestruction();

protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

private:
	// this variable will be populated to a pointer of the tank class upon begin play. Thus it can use it to get the tanks location and aim at it.
	class ATank* Tank;

	UPROPERTY(EditAnywhere)
	float FireRange = 900;

	// Timer Info
	FTimerHandle FireRateTimerHandle;
	float FireRate = 2;

	// Functions
	void ShouldFire();
};
