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
	virtual void BeginPlay() override; //make sure there is something else up the inheritance tree with this signature

	virtual void Tick(float DeltaSeconds) override;

	// Start tank moving barrel so that shot would hit where crosshair intersects world
	void AimTowardCrosshair();
	
	bool GetSightRayHitLocation(FVector& HitLocation);

	/// GETTERS
	ATank* GetControlledTank() const;
};
