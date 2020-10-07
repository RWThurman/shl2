// Copyright 2020 Sabre Dart Studios

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ServerClientTimeSyncer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHLPLUGIN_API UServerClientTimeSyncer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UServerClientTimeSyncer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Time")
		int64 GetLocalTimeInMs() const;
};
