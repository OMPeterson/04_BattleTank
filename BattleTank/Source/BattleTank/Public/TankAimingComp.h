// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComp();

	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

	void AimAt(const FVector& HitLocation, float LaunchSpeed);

private:
	UStaticMeshComponent* Barrel;
	
	void MoveBarrelTowards(const FVector& LaunchDirection);

};
