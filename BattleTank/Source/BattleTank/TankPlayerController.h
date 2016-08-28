// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be last include


UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	virtual void BeginPlay() override; //function format: make sure there is something else up the inheritance tree with this signature
	

	virtual void Tick(float DeltaSeconds) override;
	// Start tank moving barrel so that shot would hit where crosshair intersects world
	void AimTowardCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const; /// const here means that member variables cannot be altered
	bool DeprojectScreenPosToDirection(FVector& CameraLocation, FVector& AimDirection) const;
	bool GetLookVectorHitLocation(const FVector& CameraLocation, const FVector& AimDirection, FVector& HitLocation) const;

	/// GETTERS
	ATank* GetControlledTank() const;

	/// Members
	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.3333;
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000; //10 km; 10,000 m and 100 of those.
};
