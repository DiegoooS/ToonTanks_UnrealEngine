// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"

class APawnTurret;
class APawnTank;
class APlayerControllerBase;

UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Score", meta = (AllowPrivateAccess = "true"))
		int32 Score = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Score", meta = (AllowPrivateAccess = "true"))
		float HealthPercent = 1;

	APawnTank* PlayerTank;
	APlayerControllerBase* PlayerControllerRef;
	int32 TargetTurrets = 0;

	int32 GetTargetCurrentCount();
	void HandleGameStart();
	void HandleGameOver(bool PlayerWon);

public:
	void ActorDied(AActor* DeadActor);
	void ReturnHealthPercent(float& Health, float& DefaultHealth, AActor* HitActor);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
		int32 StartDelay = 4;

	UFUNCTION(BlueprintImplementableEvent)
		void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
		void GameOver(bool PlayerWon);
	UFUNCTION(BlueprintImplementableEvent)
		void SetScoreOnScreen();
	UFUNCTION(BlueprintImplementableEvent)
		void SetHealthOnScreen();
};
