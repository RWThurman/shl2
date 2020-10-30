// Copyright 2020 Sabre Dart Studios

#include "IconEffects.h"

// Sets default values for this component's properties
UIconEffects::UIconEffects()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UIconEffects::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UIconEffects::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UIconEffects::StartIconEffect(
	UWidget *targetWidgetPtr,
	const FString &effectName)
{
}

void UIconEffects::StopIconEffect(
	UWidget* targetWidgetPtr,
	const FString& effectName)
{
}