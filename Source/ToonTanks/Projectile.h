// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// components
	UPROPERTY(VisibleAnywhere, Category = "Static Mesh", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* Movement;

	// forward declare the Hit Particles (attach UI thru blueprints)
	UPROPERTY(EditAnywhere)
	class UParticleSystem* HitParticles;

	// forward declare UParticleSystemComponent (smoke trail which follows the proj)
	UPROPERTY(VisibleAnywhere)
	class UParticleSystemComponent* SmokeTrail;

	// audio variables which can play sound when projectiles is fired and hit
	UPROPERTY(EditAnywhere)
	class USoundBase* HitSound;

	UPROPERTY(EditAnywhere)
	class USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// variables
	UPROPERTY(EditAnywhere)
	float Damage = 50;

};
