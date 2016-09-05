// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComp.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComp = CreateDefaultSubobject<UTankAimingComp>(FName("TankAimingComponent"));
	LaunchSpeed = 100000; // 1000 m/s
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComp->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComp->SetTurretReference(TurretToSet);
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	//FString OurTankName = GetName();
	TankAimingComp->AimAt(HitLocation, LaunchSpeed);
}


void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire called."))
}