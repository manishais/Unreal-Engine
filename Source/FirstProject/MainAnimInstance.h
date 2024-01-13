// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class FIRSTPROJECT_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeInitializeAnimation() override;						// This function is called during the initialization of the animation instance and allows you to perform any custom setup or initialization related to animations.  provides a hook for developers to integrate custom logic or perform additional initialization steps specific to their animation instances.

	UFUNCTION(BlueprintCallable, Category = AnimationProperties)			// makes c++ functions callable from blueprints
		void UpdateAnimationProperties();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerMovement)
		float movementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerMovement)
		bool bInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = PlayerMovement)
		class APawn* Pawn;



};
