// Fill out your copyright notice in the Description page of Project Settings.


#include "Charecter/Ekagra.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEkagra::AEkagra()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEkagra::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {

		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			subsystem->AddMappingContext(EkagraMappingContext, 0);
		}
		
	}
	if (UWorld* World = GetWorld()) {
		//DrawDebugCapsule(World, )
	}
	


	
}

void AEkagra::Move(const FInputActionValue& Value)
{
	FVector2D AxisValue = Value.Get<FVector2D>();
	if (Controller) {
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation = FRotator(0.f, Rotation.Yaw, 0.f);

		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Forward, AxisValue.X);

		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Right, AxisValue.Y);

	}

}

void AEkagra::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (Controller) {
		AddControllerPitchInput(LookAxisValue.Y);
		AddControllerYawInput(LookAxisValue.X);
	}

}

void AEkagra::StartSprint()
{
	if (!bIsExhausted) {
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void AEkagra::StopSprint()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

}


// Called every frame
void AEkagra::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// check if moving
	bool bIsMoving = GetVelocity().Size() > 0.f;
	if (bIsSprinting && bIsMoving) {
		CurrentStamina -= StaminaDrainRate * DeltaTime;

		if (CurrentStamina >= 0.f) {
			CurrentStamina = 0.f;
			bIsExhausted = true;
			StopSprint();
		}


	}
	else 
	{
		if (CurrentStamina < MaxStamina) {
			CurrentStamina += StaminaRegainRate * DeltaTime;
		}

		// Player must reach 30% stamina before they can sprint again
		if (bIsExhausted && CurrentStamina >= MaxStamina * .3f) {
			bIsExhausted = false;
		}

	}
	CurrentStamina = FMath::Clamp(CurrentStamina, 0.f, MaxStamina);



}

// Called to bind functionality to input
void AEkagra::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {

	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		if (MoveAction) {
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AEkagra::Move);
		}
		if (LookAction) {
			EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AEkagra::Look);
		}
		if (SprintAction) {
			EnhancedInput->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AEkagra::StartSprint);
			EnhancedInput->BindAction(SprintAction, ETriggerEvent::Completed, this, &AEkagra::StopSprint);
		}
	}
}


