// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Classes/Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}



void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	/*auto OurTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();*/
	if (!Barrel) { return;  }
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("%s Aiming at %s"), *TankName, *AimDirection.ToString());
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// work-out difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(5); // TODO remove magic number
}
