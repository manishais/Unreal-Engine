// Fill out your copyright notice in the Description page of Project Settings.


#include "Critter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ACritter::ACritter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	meshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	meshComponent->SetupAttachment(GetRootComponent());

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(GetRootComponent());
	camera->SetRelativeLocation(FVector(-300.f, 0.f, 300.f));
	camera->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

	// AutoPossessPlayer = EAutoReceiveInput::Player0;

	currentVelocity = FVector(0.f);
	maxSpeed = 500.f;
}

// Called when the game starts or when spawned
void ACritter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACritter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector newLocation = GetActorLocation() + (currentVelocity * DeltaTime);
	SetActorLocation(newLocation);											// this way, critter moves when wasd is pressed
}

// Called to bind functionality to input
void ACritter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACritter::MoveForward);				// binding the function to the axis
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACritter::MoveRight);					// when wasd is pressed, the axis binds it to these functions, which get called. They change the velocity which when multiplied with delta time, changes the position
}

void ACritter::MoveForward(float value)
{
	currentVelocity.X = FMath::Clamp(value, -1.f, 1.f) * maxSpeed;			// clamp makes sure value never exceed min and max
}

void ACritter::MoveRight(float value)
{
	currentVelocity.Y = FMath::Clamp(value, -1.f, 1.f) * maxSpeed;
}

