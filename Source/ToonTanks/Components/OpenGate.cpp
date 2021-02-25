// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenGate.h"
#include "Engine/TriggerVolume.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UOpenGate::UOpenGate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenGate::BeginPlay()
{
	Super::BeginPlay();

	InitialZ = GetOwner()->GetActorLocation().Z;
	CurrentZ = InitialZ;

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	GateSound = GetOwner()->FindComponentByClass<UAudioComponent>();
}


// Called every frame
void UOpenGate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!GateOpener || !ActorThatOpens || !GateSound)
	{
		return;
	}

	if (GateOpener->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
	}
}

void UOpenGate::OpenDoor(float& DeltaTime)
{
	if (!AudioPlayed)
	{
		GateSound->Play();
		AudioPlayed = !AudioPlayed;
	}

	FVector GateLocation = GetOwner()->GetActorLocation();

	CurrentZ = FMath::Lerp(CurrentZ, InitialZ - GateOpenRange, DeltaTime * GateOpenSpeed);
	GateLocation.Z = CurrentZ;

	GetOwner()->SetActorLocation(GateLocation);
}

