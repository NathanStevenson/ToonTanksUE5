// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"

// Sets default values
ABasePawn::ABasePawn()
{

	// create the capsule component and set it as the pawn's root component
	capsule_comp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = capsule_comp;

	// create the base mesh and attach it to the root component
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	// create the projectile spawn point, does not need to have a visual mesh
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("Spawn Point");
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void ABasePawn::HandleDestruction(){
	// Visual and Sound Effects when Pawn dies
	
}

void ABasePawn::RotateTurret(FVector Target)
{
	// calculates the vector that points from the turret component to the target
	FVector TargetVector = Target - TurretMesh->GetComponentLocation();
	// get the rotation of the target vector, 0 out the pitch and roll so turret just rotates around Z-axis
	FRotator RotationAngle = FRotator(0, TargetVector.Rotation().Yaw, 0);

	// set the turret mesh to the correct rotation
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), RotationAngle, UGameplayStatics::GetWorldDeltaSeconds(this), 15));
}


void ABasePawn::Fire()
{
	// spawns the projectile actor in the world
    auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	Projectile->SetOwner(this);
}
