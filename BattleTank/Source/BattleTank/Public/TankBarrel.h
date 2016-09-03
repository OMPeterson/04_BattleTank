// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float DegPerSecond);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegPerSecond = 20;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevDegrees = 40;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevDegrees = -3;
	
	
};
