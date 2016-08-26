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
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *(HitLocation.ToString()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No hit."))
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//find crosshair pixel postion
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	UE_LOG(LogTemp, Warning, TEXT("Crosshair location: %s"), *ScreenLocation.ToString());

	// deproject screen position of crosshair to a world direction
	FVector CameraLocation;
	FVector WorldDirection;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, WorldDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("World Direction: %s"), *WorldDirection.ToString())
	}

	// linetrace along that direction, and see what we hit (up to max range)

	HitLocation = FVector(1.0);
	return true;
	/*
	//FHitResult Hit;
	ATank* ControlledTank = GetControlledTank();
	FVector Location;
	FRotator Rotation;
	GetPlayerViewPoint(Location, Rotation);
	FVector LineTraceEnd = Location + (Rotation.Vector() * 100000);

	DrawDebugLine(GetWorld(), ControlledTank->GetPawnViewLocation(), LineTraceEnd, FColor(255, 0, 0), false, 1, 0, 10.f);
	return true;

	GetWorld()->LineTraceSingleByObjectType(
		Hit, 
		ControlledTank->GetPawnViewLocation(),
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
		);
	HitLocation = Hit.Location;
	*/
}
