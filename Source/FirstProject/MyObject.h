// Fill out your copyright notice in the Description page of Project Settings.

#pragma once						// prevents you from inlcuding the same file twice

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyObject.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class FIRSTPROJECT_API UMyObject : public UObject
{
	GENERATED_BODY()

public:

	UMyObject();

	UPROPERTY(BlueprintReadOnly, Category = "MyVariables")
	float myFloat;

	UFUNCTION(BlueprintCallable, Category = "MyFunctions")
	void myFunction();

};
