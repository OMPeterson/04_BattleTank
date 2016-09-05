// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	if (RelativeSpeed > 1)
		RelativeSpeed = 1;
	if (RelativeSpeed < -1)
		RelativeSpeed = -1;
	//float Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("Elevate called at time %f with relative speed %f"), Time, RelativeSpeed);
	float ElevationChange = RelativeSpeed * MaxDegPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float Elevation = FMath::Clamp<float>(RawNewElevation, MinElevDegrees, MaxElevDegrees);

	SetRelativeRotation(FRotator(Elevation, 0, 0));
}


