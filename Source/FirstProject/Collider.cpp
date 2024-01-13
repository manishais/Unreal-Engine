// Fill out your copyright notice in the Description page of Project Settings.


#include "Collider.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ColliderMovementComponent.h"

// Sets default values
ACollider::ACollider()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(sphereComponent);

	sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	sphereComponent->SetupAttachment(GetRootComponent());
	sphereComponent->InitSphereRadius(40.f);				// setting the radius of the sphere
	sphereComponent->SetCollisionProfileName(TEXT("Pawn"));				// setting what it can collide with

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComponent->SetupAttachment(GetRootComponent());

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));					// this is how to hard code a mesh
	if (meshComponentAsset.Succeeded())
	{
		meshComponent->SetStaticMesh(meshComponentAsset.Object);
		meshComponent->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
		meshComponent->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));
	}

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArm->SetupAttachment(GetRootComponent());
	springArm->SetRelativeLocation(FVector(-45.f, 0.f, 0.f));		// initially looking down at the pawn
	springArm->TargetArmLength = 400.f;
	springArm->bEnableCameraLag = true;
	springArm->CameraLagSpeed = 3.0f;

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm, USpringArmComponent::SocketName);

	ourMovementComponent = CreateDefaultSubobject<UcolliderMovementComponent>(TEXT("ourMovementComponent"));
	ourMovementComponent->UpdatedComponent = RootComponent;

	cameraInput = FVector2D(0.f, 0.f);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ACollider::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator newRotation = GetActorRotation();
	newRotation.Yaw += cameraInput.X;
	SetActorRotation(newRotation);

	FRotator newSpringArmRotation = springArm->GetComponentRotation();
	// newSpringArmRotation.Pitch += cameraInput.Y;
	newSpringArmRotation.Pitch = FMath::Clamp(newSpringArmRotation.Pitch += cameraInput.Y, -80.f, -15.f);				// limits the range of up-down motion so we don't get a 360 pitch

	springArm->SetWorldRotation(newSpringArmRotation);
}

// Called to bind functionality to input
void ACollider::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACollider::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACollider::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("CameraPitch"), this, &ACollider::PitchCamera);
	PlayerInputComponent->BindAxis(TEXT("CameraYaw"), this, &ACollider::YawCamera);

}

void ACollider::MoveForward(float input)
{
	FVector forward = GetActorForwardVector();
	AddMovementInput(input * forward);
}

void ACollider::MoveRight(float input)
{
	FVector right = GetActorRightVector();

	if (ourMovementComponent)
	{
		ourMovementComponent->AddInputVector(right * input);
	}
}

void ACollider::YawCamera(float axisValue)
{
	cameraInput.X = axisValue;
}

void ACollider::PitchCamera(float axisValue)
{
	cameraInput.Y = axisValue;
}

UPawnMovementComponent* ACollider::GetMovementComponent() const
{
	return ourMovementComponent;
}