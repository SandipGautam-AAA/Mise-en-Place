// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FlashLight.h"

// Sets default values
AFlashLight::AFlashLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	FlashLightBeam = CreateDefaultSubobject<USpotLightComponent>(TEXT("FlashLightBeam"));
	FlashLightBeam->SetupAttachment(Root);
	FlashLightBeam->Intensity = DefaultIntensity;
	FlashLightBeam->SetVisibility(false);   // Start OFF

	ShadowSilhouette = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShadowSIlhouette"));
	ShadowSilhouette->SetupAttachment(FlashLightBeam);
	ShadowSilhouette->SetHiddenInGame(true); // hidden until Scare happen
	ShadowSilhouette->SetCastShadow(true);


}

// Called when the game starts or when spawned
void AFlashLight::BeginPlay()
{
	Super::BeginPlay();

	
}

void AFlashLight::StartFlickerEvent()
{
	if (!bIsOn) return;

	FlashLightBeam->SetIntensity(FlickerIntensity);
	ShadowSilhouette->SetHiddenInGame(false);

	// set timer to end scare after a very short duration
	GetWorldTimerManager().SetTimer(ScareDurationHandle, this, &AFlashLight::EndFlickerEvent, ScareDuration, false);
}

void AFlashLight::EndFlickerEvent()
{
	// Restore light and hide shadow
	FlashLightBeam->SetIntensity(DefaultIntensity);
	ShadowSilhouette->SetHiddenInGame(true);

	// If light is still on, schadule the next delay
	if (bIsOn) {
		float NextDelay = FMath::FRandRange(MinTimeBetweenScare, MaxTimeBetweenScare);
		GetWorldTimerManager().SetTimer(FlickerTimerHandle, this, &AFlashLight::StartFlickerEvent, NextDelay, false);
	}
}


// Called every frame
void AFlashLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlashLight::ToggleFlashlight()
{
	bIsOn = !bIsOn;  // true

	if (bIsOn) 
	{
		FlashLightBeam->SetVisibility(true);

		// Schedule the first random scare
		float FirstDelay = FMath::FRandRange(MinTimeBetweenScare, MaxTimeBetweenScare);
		GetWorldTimerManager().SetTimer(FlickerTimerHandle, this, &AFlashLight::StartFlickerEvent, FirstDelay, false);
	}
	else 
	{
		// Turn everything off & stop timer
		FlashLightBeam->SetVisibility(false);
		ShadowSilhouette->SetHiddenInGame(true);
		GetWorldTimerManager().ClearTimer(FlickerTimerHandle);
		GetWorldTimerManager().ClearTimer(ScareDurationHandle);
	}
}

