// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SpotLightComponent.h"
#include "FlashLight.generated.h"

UCLASS()
class MISEENPLACE_API AFlashLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlashLight();
	virtual void Tick(float DeltaTime) override;

	// Call this function from your Character's Input (e.g., Pressing 'F')
	UFUNCTION(BlueprintCallable, Category = "Flashlight")
	void ToggleFlashlight();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// --- Components ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpotLightComponent* FlashLightBeam;

	// The mesh that casts the creepy shadow (Set this to a Humanoid in BP)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ShadowSilhouette;

	// --- Logic ---
	bool bIsOn = false;
	FTimerHandle FlickerTimerHandle;
	FTimerHandle ScareDurationHandle;

	void StartFlickerEvent();
	void EndFlickerEvent();

	// --- Setting ---

	UPROPERTY(EditAnywhere, Category = "Hunted Setting")
	float DefaultIntensity = 5000.f;

	UPROPERTY(EditAnywhere, Category = "Hunted Setting")
	float FlickerIntensity = 400.f;

	UPROPERTY(EditAnywhere, Category = "Hunted Setting")
	float MinTimeBetweenScare = 4.f;

	UPROPERTY(EditAnywhere, Category = "Hunted Setting")
	float MaxTimeBetweenScare = 12.f;

	UPROPERTY(EditAnywhere, Category = "Hunted Setting")
	float ScareDuration = .2f;


};
