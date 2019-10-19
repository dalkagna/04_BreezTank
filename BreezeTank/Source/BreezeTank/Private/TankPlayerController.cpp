// Fill out your copyright notice in the Description page of Project Settings.


#include "BreezeTank.h"
#include "Tank.h"
#include "Engine/World.h"
#include "TankPlayerController.h"
//#include "GameFramework/Actor.h"

// Tick
		// Super
		// AimTowardsCrosshair();

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("Player controller ticking"));
}



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) {
		return;
	}
	
	FVector HitLocation; //out parameter
	if (GetSightRayHitLocation(HitLocation)) // Has side-effect, is going to line trace
	{
		GetControlledTank()->AimAt(HitLocation);
	}// Tell controlled tank to aim at this point
}
	
	 


// get world location if line trace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());

	// de-project the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, HitLocation);

	}
	// line-trace along that look direction, and see what we hit (up to max range)
	return true;

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
					HitResult,
					StartLocation,
					EndLocation,
					ECollisionChannel::ECC_Visibility)
			)
		{
			HitLocation = HitResult.Location;
			return true;
		}
	HitLocation = FVector(0);
	return false; // line trace didn't succeed
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // to be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection);
	
}
