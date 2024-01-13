// Fill out your copyright notice in the Description page of Project Settings.


#include "Floater.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFloater::AFloater()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomStaticMesh"));				// creates a static mesh component
	// variable = CreateDefaultSubobject<typeOfObjectCreated>(parameter - in this case is a text macro)
	// CreateDefaultSubobject is a template function i.e. it creates new object, but you tell what type is is
	// need the parenthesis () because it is a function call

	InitialLocation = FVector(0.0f);
	PlacedLocation = FVector(0.0f);
	WorldOrigin = FVector(0.0f);
	InitialDirection = FVector(0.0f);
	bInitializeFloaterLocations = false;
	bShouldFloat = false;
	InitialForce = FVector(20000000, 0.0f, 0.0f);
	InitialTorque = FVector(20000000, 0.0f, 0.0f);
	RunningTime = 0.0f;
	A = 0.0f;
	B = 0.0f;
	C = 0.0f;
	D = 0.0f;
}

// Called when the game starts or when spawned
void AFloater::BeginPlay()
{
	Super::BeginPlay();

	float InitialX = FMath::FRandRange(-500.f, 500.f);
	float InitialY = FMath::FRandRange(-500.f, 500.f);
	float InitialZ = FMath::FRandRange(0.f, 500.f);

	InitialLocation.X = InitialX;
	InitialLocation.Y = InitialY;
	InitialLocation.Z = InitialZ;


	//	InitialLocation *= 500.f;				// scaling the intital location by 500

	PlacedLocation = GetActorLocation();

	if (bInitializeFloaterLocations)
	{
		SetActorLocation(InitialLocation);			// when begin play is called, the actor i.e. the floater is set to the location of the fvector - in this case, (0, 0, 0)
	}

	BaseZLocation = PlacedLocation.Z;
}

// Called every frame
void AFloater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldFloat)
	{
		// FHitResult HitResult;				// created only because addactorlocaloffset requires the parameter
		// AddActorLocalOffset(FVector(InitialDirection), true, &HitResult);					// setting bSweep to true, even if simulate physics is off, will ensure that collisions occur. If false and simultae physics is also off, then collisions do not occur.
		//FVector HitLocation = HitResult.Location;

		// UE_LOG(LogTemp, Warning, TEXT("Hit Location: X = %f, Y = %f, Z = %f"), HitLocation.X, HitLocation.Y, HitLocation.Z);

		FVector newLocation = GetActorLocation();
		newLocation.Z = BaseZLocation + A * FMath::Sin(B * RunningTime - C) + D;
		SetActorLocation(newLocation);
		RunningTime += DeltaTime;
	}
}

