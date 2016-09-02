// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComp.h"


// Sets default values for this component's properties
UTankAimingComp::UTankAimingComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComp::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}


void UTankAimingComp::AimAt(const FVector& HitLocation, float LaunchSpeed)
{
	//FString Name = GetOwner()->GetName();
	
	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s from %s"), *Name, *(HitLocation.ToString()), *(Barrel->GetComponentLocation().ToString()));
	if (Barrel)
	{
		FVector OutLaunchVelocity;
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

		if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed))
		{
			FVector LaunchDirection = OutLaunchVelocity.GetSafeNormal();
			
			MoveBarrelTowards(LaunchDirection);
			
			FString TankName = GetOwner()->GetName();
			UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *TankName, *LaunchDirection.ToString());
		}	
	}
}

void UTankAimingComp::MoveBarrelTowards(const FVector& LaunchDirection)
{
	// adjust rotation of turret to  match x--y direction
	// adjust elevation of barrel to match z direction
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimRotation = LaunchDirection.Rotation();
	FRotator DeltaRotator = AimRotation - BarrelRotation;
	UE_LOG(LogTemp, Warning, TEXT("AimRotation = %s"), *AimRotation.ToString())
}