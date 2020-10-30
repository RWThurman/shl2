// Copyright 2020 Sabre Dart Studios

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/Widget.h"
#include "IconEffects.generated.h"

class UWidget;

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

	UFUNCTION(BlueprintCallable, Category = "IconEffects")
		void StartIconEffect(
			UWidget *targetWidgetPtr,
			const FString &effectName);

	UFUNCTION(BlueprintCallable, Category = "IconEffects")
		void StopIconEffect(
			UWidget* targetWidgetPtr,
			const FString& effectName);
};
