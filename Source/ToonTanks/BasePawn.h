// Fill out your copyright notice in the Description page of Project Settings.

// pragma once makes sure that include files are only included once in the project
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	// cleans up the pawn when it is dead
	void HandleDestruction();

protected:
	// function that takes in a location and rotates the pawn to that target location
	void RotateTurret(FVector Target);

	// function that allows the turrets and the tank to fire projectiles
	void Fire();

private:
	// the root component that helps when detecting collision
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Capsule", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* capsule_comp;

	// forward declare the Death Explosion Particles
	UPROPERTY(EditAnywhere)
	class UParticleSystem* DeathParticles;

	// audio to play when the Tower/Tank dies
	UPROPERTY(EditAnywhere)
	class USoundBase* DeathSound;

	// camera shake for new UE5.1 
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;

	// static mesh components for the tanks base and the turret (different so they can move independently of each other)
	// included by default. do not need to forward to declare with "class"
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Static Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Static Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawn Point", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

};
