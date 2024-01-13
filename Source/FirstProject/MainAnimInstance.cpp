// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMainAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}
}

void UMainAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr)
	{
		Pawn = TryGetPawnOwner();
	}

	if (Pawn)
	{
		FVector Speed = Pawn->GetVelocity();
		FVector lateralSpeed = FVector(Speed.X, Speed.Y, 0.f);			// only care about running/jumping speed so no z value
		movementSpeed = lateralSpeed.Size();			// magnitude of the 2d vector

		bInAir = Pawn->GetMovementComponent()->IsFalling();				// can determine if pawn is in air by checking if it is falling
	}
}