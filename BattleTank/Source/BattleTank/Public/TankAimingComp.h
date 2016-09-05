// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComp.generated.h"

class UTankBarrel; // forward declaration
class UTankTurret;

//holds parameters for barrel properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComp();

	void SetBarrelReference(UTankBarrel* BarrelToSet);
	void SetTurretReference(UTankTurret* TurretToSet);

	void AimAt(const FVector& HitLocation, float LaunchSpeed);

private:
	UTankBarrel* Barrel;
	UTankTurret* Turret;
	
	void MoveBarrelTowards(const FVector& LaunchDirection);

};
