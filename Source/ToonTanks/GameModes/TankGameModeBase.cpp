// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Get references and win/lose condition
	// Call HandleGameStart() to initialise the start countdown, turret activation, pawn check etc
	HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	// Check what type of actor died. If turret, tally. If Player -> go to lose condition
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();

		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
		HandleGameOver(false);
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();

		Score += 10;
		SetScoreOnScreen();
		UE_LOG(LogTemp, Warning, TEXT("%i"), Score);
		TargetTurrets -= 1;

		if (TargetTurrets <= 0)
		{
			HandleGameOver(true);
		}
	}
}

void ATankGameModeBase::ReturnHealthPercent(float& Health, float& DefaultHealth, AActor* HitActor)
{
	if (HitActor == PlayerTank)
	{
		HealthPercent = ((Health * 100) / DefaultHealth) * 0.01f;
		SetHealthOnScreen();
	}
}

void ATankGameModeBase::HandleGameStart()
{
	// initialise the start countdown, turret activation, pawn check etc
	// Call blueprint version GameStart()

	TargetTurrets = GetTargetCurrentCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	Score = 0;

	GameStart();

	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(
			PlayerControllerRef, 
			&APlayerControllerBase::SetPlayerEnabledState, 
			true
		);

		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	// See if PLayer has destroyed all the turrets, show win result
	// else if turret destroyed player, show lost result
	// Call blueprint version gameover(bool)
	GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetTargetCurrentCount()
{
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}