// Fill out your copyright notice in the Description page of Project Settings.

#include "MyObject.h"

UMyObject::UMyObject()
{
	myFloat = 0;
}

void UMyObject::myFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("This is our wanring text!"));			// UE_LOG logs, LogTemp means it is temporary, Warning means text is yellow and marked as warning 
}