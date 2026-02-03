// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FlickringLight.h"

// Sets default values
AFlickringLight::AFlickringLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	RootComponent = PointLight;
}

// Called when the game starts or when spawned
void AFlickringLight::BeginPlay()
{
	Super::BeginPlay();

	UpdateFlicker();
	
}

void AFlickringLight::UpdateFlicker()
{
	if (PointLight) {
		// 1. Pick a random intensity between your Min and Max
		float NewIntensity = FMath::FRandRange(FlickerIntensity, DefaultIntensity);
		PointLight->SetIntensity(NewIntensity);

		// 2. Pick a random delay for the "jitter" effect
		float NextDelay = FMath::FRandRange(MinTimeBetweenFlicker, MaxTimeBetweenFlicker);
		
		// 3. Schedule the next update
		GetWorldTimerManager().SetTimer(FlickerTimerHandel, this, &AFlickringLight::UpdateFlicker, NextDelay, false);
	}

}

// Called every frame
void AFlickringLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}

