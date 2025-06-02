// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AProjectile::AProjectile()
{
	// create the base mesh in the constructor and assign the root component to it
 	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;

	SmokeTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	SmokeTrail->SetupAttachment(RootComponent); // attach to root

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->InitialSpeed = 1000;
	Movement->MaxSpeed = 1500;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	BaseMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	// play the projectile audio when firing after the projectile has been spawned
	if (LaunchSound){
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Function bound in BeginPlay to Component Hit delegate
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// figure out the player who launched the projectile
	auto MyOwner = GetOwner();
	if(MyOwner == nullptr) {
		this->Destroy();
		return;
	}
	auto MyOwnerInstigator = MyOwner->GetInstigatorController();

	// Apply Damage to the actor and then delete the projectile if other actor exists, is not a projectile, and not the thing firing it
	// change this to cast of projectile to see if true - rn bullets destroy other bullets
	if(OtherActor && OtherActor != this && OtherActor != MyOwner){
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, UDamageType::StaticClass());
		// spawn the hit particles after any OnHit the projectile hits
		if (HitParticles){
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
		}
		// play the audio when the projectile hits something
		if (HitSound){
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}
		// shake the screen a little bit when the projectile hits something
		if (HitCameraShakeClass) {
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}
	// always want to destroy projectile when it hits something so nothing stays around
	this->Destroy();
}