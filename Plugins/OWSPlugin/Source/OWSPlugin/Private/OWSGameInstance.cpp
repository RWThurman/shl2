// Fill out your copyright notice in the Description page of Project Settings.

#include "OWSGameInstance.h"
#include "OWSPlugin.h"
#include "Runtime/MoviePlayer/Public/MoviePlayer.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "OWSPlayerController.h"

void UOWSGameInstance::Init()
{
	UGameInstance::Init();

	Http = &FHttpModule::Get();

	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UOWSGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UOWSGameInstance::EndLoadingScreen);
}

void UOWSGameInstance::BeginLoadingScreen(const FString& MapName)
{
	if (!IsRunningDedicatedServer())
	{
		RPGBeginLoadingScreen();

		/*FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
		LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();

		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);*/
	}
}



void UOWSGameInstance::EndLoadingScreen(UWorld* world)
{
	if (!IsRunningDedicatedServer())
	{
		RPGEndLoadingScreen();
	}
}

void UOWSGameInstance::HideLoadingScreen()
{
	if (!IsRunningDedicatedServer())
	{
		HideLoadingDialog();
	}
}

TSubclassOf<class AActor> UOWSGameInstance::LoadWeaponActorClassFromPath(FString WeaponActorClassPath)
{
	auto cls = StaticLoadObject(UObject::StaticClass(), nullptr, *WeaponActorClassPath);

	if (cls)
	{
		UBlueprint * bp = Cast<UBlueprint>(cls);
		if (bp)
		{
			return (UClass*)bp->GeneratedClass;
		}
	}

	return NULL;
}

UStaticMesh* UOWSGameInstance::LoadStaticMeshFromPath(FString StaticMeshPath)
{
	UStaticMesh* tempStaticMesh;
	tempStaticMesh = LoadObject<UStaticMesh>(NULL, *StaticMeshPath, NULL, LOAD_None, NULL);

	if (!tempStaticMesh)
	{
		UE_LOG(OWS, Error, TEXT("LoadStaticMeshFromPath - Error loading Static Mesh: %s"), *StaticMeshPath);
		return NULL;
	}

	return tempStaticMesh;
}

USkeletalMesh* UOWSGameInstance::LoadSkeletalMeshFromPath(FString SkeletalMeshPath)
{
	USkeletalMesh* tempSkeletalMesh;
	tempSkeletalMesh = LoadObject<USkeletalMesh>(NULL, *SkeletalMeshPath, NULL, LOAD_None, NULL);

	if (!tempSkeletalMesh)
	{
		UE_LOG(OWS, Error, TEXT("LoadSkeletalMeshFromPath - Error loading Skeletal Mesh: %s"), *SkeletalMeshPath);
		return NULL;
	}

	return tempSkeletalMesh;
}

USkeleton* UOWSGameInstance::LoadSkeletonFromPath(FString SkeletonPath)
{
	USkeleton* tempSkeleton;
	tempSkeleton = LoadObject<USkeleton>(NULL, *SkeletonPath, NULL, LOAD_None, NULL);

	if (!tempSkeleton)
	{
		UE_LOG(OWS, Error, TEXT("LoadSkeletonFromPath - Error loading Skeleton: %s"), *SkeletonPath);
		return NULL;
	}

	return tempSkeleton;
}

UMaterialInstance* UOWSGameInstance::LoadMaterialInstanceFromPath(FString MaterialInstancePath)
{
	UMaterialInstance* tempMaterial;
	tempMaterial = LoadObject<UMaterialInstance>(NULL, *MaterialInstancePath, NULL, LOAD_None, NULL);

	if (!tempMaterial)
	{
		UE_LOG(OWS, Error, TEXT("LoadMaterialInstanceFromPath - Error loading Material Instance: %s"), *MaterialInstancePath);
		return NULL;
	}

	return tempMaterial;
}

/*
FString UOWSGameInstance::EncryptWithAES(FString InputString)
{
	int32 Size = InputString.Len(); // Calculates length of the input string

	TCHAR *String = InputString.GetCharArray().GetData();    // Turn input string...
	uint8* BytesString = (uint8*)(String);                    // ...into byte array

	FString Key = "FF82B5451E21C090AE76622AAF24BCB0";                                            // Choose a key then...
	TCHAR *KeyTChar = Key.GetCharArray().GetData();            // ...turn key string...
	ANSICHAR *KeyAnsi = (ANSICHAR*)TCHAR_TO_ANSI(KeyTChar); // ...into ANSICHAR array.

	FAES::EncryptData(BytesString, Size, KeyAnsi); // encrypt.

	TArray<uint8> EncryptedByteArray;                        // Define a new array to store the output data
	EncryptedByteArray.Append(BytesString, Size);            // Move output of the FAES functions to this array
	FString output = FBase64::Encode(EncryptedByteArray);    // Turn array into FString
	return output;
}

FString UOWSGameInstance::DecryptWithAES(FString InputString)
{
	int32 Size = InputString.Len(); // Calculates length of the input string

	TCHAR *String = InputString.GetCharArray().GetData();    // Turn input string...
	uint8* BytesString = (uint8*)(String);                    // ...into byte array

	FString Key = "FF82B5451E21C090AE76622AAF24BCB0";                                            // Choose a key then...
	TCHAR *KeyTChar = Key.GetCharArray().GetData();            // ...turn key string...
	ANSICHAR *KeyAnsi = (ANSICHAR*)TCHAR_TO_ANSI(KeyTChar);

	FAES::DecryptData(BytesString, Size, KeyAnsi); // Decrypt or...

	TArray<uint8> EncryptedByteArray;                        // Define a new array to store the output data
	EncryptedByteArray.Append(BytesString, Size);            // Move output of the FAES functions to this array
	FString output = FBase64::Encode(EncryptedByteArray);    // Turn array into FString
	return output;
}
*/

FString UOWSGameInstance::SerializeStructToJSONString(const UStruct* StructToSerialize)
{
	FString TempOutputString;
	for (TFieldIterator<UProperty> PropIt(StructToSerialize->GetClass()); PropIt; ++PropIt)
	{
		UProperty* Property = *PropIt;
		TempOutputString += Property->GetNameCPP();
	}

	return TempOutputString;
}


UClass* UOWSGameInstance::FindClass(FString ClassName) const
{
	UObject* ClassPackage = ANY_PACKAGE;
	UClass* Result = FindObject<UClass>(ClassPackage, *ClassName);

	return Result;
}

//This only works if the ability is already in memory.  Use LoadGameplayAbilityClass instead
TSubclassOf<UGameplayAbility> UOWSGameInstance::FindGameplayAbilityClass(FString ClassName) const
{
	UObject* ClassPackage = ANY_PACKAGE;
	UClass* Result = FindObject<UClass>(ClassPackage, *ClassName);

	TSubclassOf<UGameplayAbility> GameplayAbilityClass = Result;

	if (GameplayAbilityClass)
		return Result;
	else
		return nullptr;
}


TSubclassOf<UGameplayAbility> UOWSGameInstance::LoadGameplayAbilityClass(FString PathToGameplayAbilityClass) const
{
	return LoadClass<UGameplayAbility>(NULL, *PathToGameplayAbilityClass, NULL, LOAD_None, NULL);
}