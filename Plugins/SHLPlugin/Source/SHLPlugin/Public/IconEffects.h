// Copyright 2020 Sabre Dart Studios

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IconEffects.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHLPLUGIN_API UIconEffects : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIconEffects();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
