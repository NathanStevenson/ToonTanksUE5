// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

	// default constructor for the tank pawn
	public:
		ATank();

		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		// Called every frame
		virtual void Tick(float DeltaTime) override;
	
	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
	
	// necessary variables specific to the ATank class
	private:
		// Components
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spring Arm", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComponent;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

		// Variables controlling movement
		UPROPERTY(EditAnywhere, Category = "Movement")
		float Speed = 400.f;

		UPROPERTY(EditAnywhere, Category = "Movement")
		float TurnRate = 120.f;

		// Functions for binding to key presses
		void MoveForward(float value);
		void Turn(float value);

		// Reference to the player controller
		APlayerController* PlayerControllerRef;
};
