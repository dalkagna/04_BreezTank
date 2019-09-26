// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))

class BREEZETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float DegreesPerSecond);

	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 20; // sensible default

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDegrees = 40; // sensisble default

	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDegrees = 0; 
};
