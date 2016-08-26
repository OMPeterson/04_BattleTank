// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay(); //Calls parent BeginPlays

	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController Possessing tank %s"), *(ControlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TankPlayerController not possessing any tank"));
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetControlledTank())
		return;

	FVector HitLocation; //Out parameter
	
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hitlocation: %s"), *(HitLocation.ToString()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No hit."))
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation)
{
	//FHitResult Hit;
	ATank* ControlledTank = GetControlledTank();
	FVector LineTraceEnd = ControlledTank->GetPawnViewLocation() + (ControlledTank->GetViewRotation().Vector() * 100);

	DrawDebugLine(GetWorld(), ControlledTank->GetPawnViewLocation(), LineTraceEnd, FColor(255, 0, 0), false, 0, 0, 10.f);

	/*GetWorld()->LineTraceSingleByObjectType(
		Hit, 
		ControlledTank->GetPawnViewLocation(),
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
		);
	HitLocation = Hit.Location;
	*/
}
