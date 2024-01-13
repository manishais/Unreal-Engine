// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Collider.generated.h"

UCLASS()
class FIRSTPROJECT_API ACollider : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* meshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USphereComponent* sphereComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UCameraComponent* camera;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UcolliderMovementComponent* ourMovementComponent;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	FORCEINLINE UStaticMeshComponent* getMeshComponent()
	{
		return meshComponent;
	}

	FORCEINLINE void setMeshComponent(UStaticMeshComponent* mesh)
	{
		meshComponent = mesh;
	}

	FORCEINLINE USphereComponent* getSphereComponent()
	{
		return sphereComponent;
	}

	FORCEINLINE void setSphereComponent(USphereComponent* sphere)
	{
		sphereComponent = sphere;
	}
	FORCEINLINE UCameraComponent* getCameraComponent()
	{
		return camera;
	}

	FORCEINLINE void setCameraComponent(UCameraComponent* cameraIn)
	{
		camera = cameraIn;
	}

	FORCEINLINE USpringArmComponent* getSpringArmComponent()
	{
		return springArm;
	}

	FORCEINLINE void setSpringArm(USpringArmComponent* springArmIn)
	{
		springArm = springArmIn;
	}

private:
	void MoveForward(float input);
	void MoveRight(float input);
	void YawCamera(float axisValue);
	void PitchCamera(float axisValue);
	FVector2D cameraInput;

};
