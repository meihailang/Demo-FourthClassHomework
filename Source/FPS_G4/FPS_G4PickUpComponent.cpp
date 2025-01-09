// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPS_G4PickUpComponent.h"

UFPS_G4PickUpComponent::UFPS_G4PickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UFPS_G4PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UFPS_G4PickUpComponent::OnSphereBeginOverlap);
}

void UFPS_G4PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AFPS_G4Character* Character = Cast<AFPS_G4Character>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
