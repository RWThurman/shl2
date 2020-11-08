// Copyright 2020 Sabre Dart Studios

#include "IconEffects.h"
#include "IconEffectUser.h"


// Sets default values for this component's properties
UIconEffects::UIconEffects()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}

// Called when the game starts
void UIconEffects::BeginPlay()
{
	Super::BeginPlay();

	// ...
	LoadIconEffectsData();
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
	bool bIsImplemented = targetWidgetPtr->GetClass()->ImplementsInterface(UIconEffectUser::StaticClass());

	if (bIsImplemented)
	{
		FIconEffectsData data;

		if (FindEffectInfo(effectName, data))
		{
			IIconEffectUser::Execute_StartIconEffect(targetWidgetPtr, effectName);
		}
	}
}

void UIconEffects::StopIconEffect(
	UWidget* targetWidgetPtr,
	const FString& effectName)
{
	bool bIsImplemented = targetWidgetPtr->GetClass()->ImplementsInterface(UIconEffectUser::StaticClass());

	if (bIsImplemented)
	{
		FIconEffectsData data;

		if (FindEffectInfo(effectName, data))
		{
			IIconEffectUser::Execute_StopIconEffect(targetWidgetPtr, effectName);
		}
	}
}

void UIconEffects::LoadIconEffectsData()
{
	if (nullptr == pDataTable)
	{
		pDataTable = LoadObject<UDataTable>(nullptr, UTF8_TO_TCHAR("DataTable'/SHLPlugin/Data/IconEffectsDataTable.IconEffectsDataTable'"));
	}
}


bool UIconEffects::FindEffectInfo(
	const FString& effectName,
	FIconEffectsData& effectInfo)
{
	if (nullptr == pDataTable)
	{
		return false;
	}

	FIconEffectsData* pIconEffectsData = pDataTable->FindRow<FIconEffectsData>(FName(effectName), nullptr);

	if (nullptr != pIconEffectsData)
	{
		effectInfo = *pIconEffectsData;

		return true;
	}

	return false;
}