// Fill out your copyright notice in the Description page of Project Settings.

#include "BreezeTank.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()

{
	Super::BeginPlay();
	}
void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());
	if (PlayerTank)
	{
		// move towards the player
		// aim at the player

		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire(); 
	}
}
