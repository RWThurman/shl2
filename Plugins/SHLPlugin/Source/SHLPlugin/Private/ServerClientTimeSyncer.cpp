// Copyright 2020 Sabre Dart Studios


#include "ServerClientTimeSyncer.h"
#include <sys/types.h>
#include <sys/timeb.h>

// Sets default values for this component's properties
UServerClientTimeSyncer::UServerClientTimeSyncer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UServerClientTimeSyncer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UServerClientTimeSyncer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

int64 UServerClientTimeSyncer::GetLocalTimeInMs() const
{
	struct __timeb64 timebuffer;

	// BWT Time Code.
	_ftime64_s(&timebuffer);

	return int64(timebuffer.time) * 1000 + int64(timebuffer.millitm);
}
