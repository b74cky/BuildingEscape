// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	
	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	InitialDoorAngle = Owner->GetActorRotation();
	
}

void UOpenDoor::OpenDoor() {
	
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor() {

	Owner->SetActorRotation(FRotator(0.f, InitialDoorAngle.Yaw, 0.f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Triger Volume
	// If the ActorThatOpens is in the volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens)) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetRealTimeSeconds();
	}

	// Check if it's time to close the door
	if (GetWorld()->GetRealTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		CloseDoor();
	}


}

