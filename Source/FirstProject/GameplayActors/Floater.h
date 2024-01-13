// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floater.generated.h"

UCLASS()
class FIRSTPROJECT_API AFloater : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFloater();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ActorMeshComponents")
	UStaticMeshComponent* StaticMesh;

	// so before we hit play, we click on the floater, go to FloaterVectors and enter a vector. After we hit begin play, that floater will change its positiion to the entered vector. This is what is meant by "EditInstanceOnly"
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Floater Variables")			// ediatble only on an instance of the floater
	FVector InitialLocation;			// location used by SetAtorLocation() when begin play is called

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Floater Variables")				// vsisible, not editable
	FVector PlacedLocation;					// location of the actor when dragged in from the editor

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Floater Variables")
	bool bInitializeFloaterLocations;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadonly, Category = "Floater Variables")				// not visible to instances - so can be seen only in viewport
	FVector WorldOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")			// can edit in instance, default etc.
	FVector InitialDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floater Variables")
	bool bShouldFloat;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Floater Variables")
	FVector InitialForce;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Floater Variables")
	FVector InitialTorque;

	// Amplitude = how much we oscillate up and down
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
		float A;

	// Period = 2 * PI / (absolute value of B)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
		float B;

	// Phase Shift = (C / B)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
		float C;

	// Vertical Shift = D
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floater Variables")
		float D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floater Variables")
		bool test;

private:
	float RunningTime;
	float BaseZLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
