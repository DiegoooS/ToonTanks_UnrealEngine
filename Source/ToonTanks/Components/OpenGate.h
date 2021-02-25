// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenGate.generated.h"

class ATriggerVolume;
class UAudioComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UOpenGate : public UActorComponent
{
	GENERATED_BODY()
private:

	// VARIABLES
	UPROPERTY(EditAnywhere, Category = "Audio")
		UAudioComponent* GateSound;
	UPROPERTY(EditAnywhere, Category = "Open")
		ATriggerVolume* GateOpener;
	UPROPERTY()
		AActor* ActorThatOpens;
	UPROPERTY(EditAnywhere, Category = "Open")
		float GateOpenRange = -200;
	UPROPERTY(EditAnywhere, Category = "Open")
		float GateOpenSpeed = 2;

	float InitialZ;
	float CurrentZ;
	bool AudioPlayed = false;

	// FUNCTIONS
	void OpenDoor(float& DeltaTime);

public:	
	// Sets default values for this component's properties
	UOpenGate();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;	
};
