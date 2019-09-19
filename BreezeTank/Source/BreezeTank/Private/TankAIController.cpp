// Fill out your copyright notice in the Description page of Project Settings.

#include "BreezeTank.h"
#include "Engine/World.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()

{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *(PlayerTank->GetName()));
	}
}
void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (GetPlayerTank())
	{
		// move towards the player
		// aim at the player
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		// fire if ready
	}
}
ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {
		return nullptr;
	}

	return Cast<ATank>(PlayerPawn);

}