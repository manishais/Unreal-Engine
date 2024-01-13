// Fill out your copyright notice in the Description page of Project Settings.

#include "Main.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMain::AMain()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create cameraBoom (pulls towards the player if there is a collision
	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("cAMERAbOOM"));
	cameraBoom->SetupAttachment(GetRootComponent());
	cameraBoom->TargetArmLength = 600.f;			// camera follows at this distance
	cameraBoom->bUsePawnControlRotation = true;		// rotate arm based on controller

	// set size for colisio capsule
	GetCapsuleComponent()->SetCapsuleSize(88.f, 34.f);			// got numbers from blueprint (main_bp)

	// create follow camera
	cameraFollow = CreateDefaultSubobject<UCameraComponent>(TEXT("cameraFollow"));
	cameraFollow->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);				// socket allows you to add something to it - when character picks up a sword, youcan attach the socket to the hand bone so that the sword is attached tp chars hand
	cameraFollow->bUsePawnControlRotation = false;		// attach the camera to the end of the boom and let the boom adjust to match the conteoller 

	BaseTurnRate = 65.f;
	BaseLookUpRate = 65.f;

	// ensuring player does not rotate, only camera does
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Confiure character movemeny
	GetCharacterMovement()->bOrientRotationToMovement = true;			// character moves in direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.f, 0.0f);		// ... at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 650.f;
	GetCharacterMovement()->AirControl = 0.2f;


}


// Called when the game starts or when spawned
void AMain::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMain::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMain::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMain::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AMain::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &AMain::AddControllerYawInput);

	PlayerInputComponent->BindAxis("TurnRate", this, &AMain::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMain::LookUpRate);
}

void AMain::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		// Find out which way is forward
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, rotation.Yaw, 0.f);

		const FVector direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);		// accessing a unit vector in the direction of x axis for this particular rotator
		AddMovementInput(direction, Value);
	}
}

void AMain::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.0f)
	{
		// Find out which way is right
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, rotation.Yaw, 0.f);

		const FVector direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);		// accessing a unit vector in the direction of y axis for this particular rotator
		AddMovementInput(direction, Value);
	}
}

void AMain::TurnAtRate(float rate)
{
	AddControllerYawInput(rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMain::LookUpRate(float rate)
{
	AddControllerPitchInput(rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

