// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "FlickringLight.generated.h"

UCLASS()
class MISEENPLACE_API AFlickringLight : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFlickringLight();

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPointLightComponent* PointLight;

	// The logic to change intensity
	void UpdateFlicker();

	FTimerHandle FlickerTimerHandel;

	// --- Flicker Setting ---
	UPROPERTY(EditAnywhere, Category = "Flicker Settings")
	float DefaultIntensity = 5000.f;

	UPROPERTY(EditAnywhere, Category = "Flicker Settings")
	float FlickerIntensity = 3500.f;

	UPROPERTY(EditAnywhere, Category = "Flicker Settings")
	float MinTimeBetweenFlicker = .01f;

	UPROPERTY(EditAnywhere, Category = "Flicker Settings")
	float MaxTimeBetweenFlicker = .07f;
};
