// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Tank default constructor
ATank::ATank()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // create the default subobjects for the correct classes
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

    // attach the spring arm to the root and camera to spring arm
    SpringArmComponent->SetupAttachment(RootComponent);    
    CameraComponent->SetupAttachment(SpringArmComponent);    
}


// Called when the game starts or when spawned
void ATank::BeginPlay(){
	Super::BeginPlay();
    TankPlayerController = Cast<APlayerController>(GetController());
}


// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    // good practice to ensure pointer is not null before using
    if(TankPlayerController){
        // post function call this will be populated with info about the hit event
        FHitResult HitResult;
        // want to use ECC_Visibility. Many objects block visbility channel by default which is what we want
        TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

        // rotates the turret with respect to the cursor
        RotateTurret(HitResult.ImpactPoint);
    }
}

// cleans up the pawn when dies; for tank just want to hide it not completely destroy so that respawn can happen
void ATank::HandleDestruction(){
    Super::HandleDestruction();
    SetActorHiddenInGame(true); // hides the tank
    SetActorTickEnabled(false); // stops ticking to save resources
}

// this function is inherited from parent class and overrides it. Uses its functionality but adds extra custom functions to input mappings in UE5
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}


// when W or S is pressed value will be either -1, 0, 1. And we will add the appropriate offset to make the tank move forward
void ATank::MoveForward(float value)
{    
    // go forward by the value, times variable speed, times the delta time for consistent frame rate movement
    AddActorLocalOffset(FVector((value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this)), 0, 0), true);
}

// when A or D is pressed this will allow the tank to rotate either right or left appropriately
void ATank::Turn(float value)
{
    AddActorLocalRotation(FRotator(0, (value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this)), 0), true);
}