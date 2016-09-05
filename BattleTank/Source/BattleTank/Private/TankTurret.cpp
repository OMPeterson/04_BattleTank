// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	if (RelativeSpeed > 1)
		RelativeSpeed = 1;
	if (RelativeSpeed < -1)
		RelativeSpeed = -1;
	//float Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("Elevate called at time %f with relative speed %f"), Time, RelativeSpeed);
	float RotationChange = RelativeSpeed * MaxDegPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}



