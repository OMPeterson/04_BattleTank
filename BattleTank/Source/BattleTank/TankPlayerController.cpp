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
	FVector CameraLocation, AimDirection;
	if (DeprojectScreenPosToDirection(CameraLocation, AimDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("World Direction: %s"), *AimDirection.ToString());
		FVector HitLocation;
		if (GetLookVectorHitLocation(CameraLocation, AimDirection, HitLocation))
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
		}
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

bool ATankPlayerController::DeprojectScreenPosToDirection(FVector& CameraLocation, FVector& AimDirection) const
{
	// Find crosshair pixel position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	UE_LOG(LogTemp, Warning, TEXT("Crosshair location: %s"), *ScreenLocation.ToString());

	// Deproject screen position of crosshair to a world direction
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, AimDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector& CameraLocation, const FVector& AimDirection, FVector& HitLocation) const
{
	FHitResult Hit;
	//FVector CameraLocation = PlayerCameraManager->GetCameraLocation();
	if (GetWorld()->LineTraceSingleByChannel(
		Hit,
		CameraLocation,
		CameraLocation + (AimDirection * LineTraceRange),
		ECollisionChannel::ECC_Visibility
		))
	{
		HitLocation = Hit.Location;
		return true;
	}
	HitLocation = FVector(0.0);
	return false;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}