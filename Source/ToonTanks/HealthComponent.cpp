// Fill out your copyright notice in the Description page of Project Settings.
#include "Kismet/GameplayStatics.h"

#include "HealthComponent.h"
#include "ToonTanksGameMode.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	// set health to the custom max health we chose for this component
	Health = MaxHealth;

	// gets the current GameModeBase of the World (if custom is set)
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this)); // returns GameModeBase which ToonTanks inherits from so Cast

	// Damage taken bound to actor's damage event. Whenever actor takes damage delegate will call this function
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


// function that is bound in BeginPlay to component damage delegate
void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	if(Damage > 0){
		Health -= Damage;
	}
	UE_LOG(LogTemp, Display, TEXT("Actor Hurt: %s Health: %f"), *DamagedActor->GetName(), Health);
	// can be simple enough to call this->Destroy
	// better to go thru the GameMode though so special effects can happen upon death; tank can be respawned;
	// towers destroyed simply; but going through GameMode gives more real game control with levels etc
	if (Health <= 0 && ToonTanksGameMode) {
		ToonTanksGameMode->ActorDied(DamagedActor);
	}
}

