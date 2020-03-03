// Fill out your copyright notice in the Description page of Project Settings.

#include "OWSLoginWidget.h"
#include "OWSPlugin.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "OWSPlayerController.h"
#include "Runtime/Core/Public/Misc/ConfigCacheIni.h"


void UOWSLoginWidget::LoginAndCreateSession(FString Email, FString Password)
{
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("RPGAPICustomerKey"),
		RPGAPICustomerKey,
		GGameIni
	);

	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("RPGAPIPath"),
		RPGAPIPath,
		GGameIni
	);

	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("OWS2APIPath"),
		OWS2APIPath,
		GGameIni
	);

	Http = &FHttpModule::Get();
	Http->SetHttpTimeout(LoginTimeout); //Set timeout

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UOWSLoginWidget::OnLoginAndCreateSessionResponseReceived);

	FString url = FString(OWS2APIPath + "api/Users/LoginAndCreateSession");

	//Trim whitespace
	Email.TrimStartAndEndInline();
	Password.TrimStartAndEndInline();

	/*
	FString PostParameters = FString(TEXT("{ \"Email\": \"")) + Email + FString(TEXT("\", "))
		+ FString(TEXT("\"Password\": \"")) + Password + FString(TEXT("\" }"));
	*/

	TArray<FStringFormatArg> FormatParams;
	FormatParams.Add(Email);
	FormatParams.Add(Password);
	FString PostParameters = FString::Format(TEXT("{ \"Email\": \"{0}\", \"Password\": \"{1}\" }"), FormatParams);

	Request->SetURL(url);
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->SetHeader(TEXT("X-CustomerGUID"), RPGAPICustomerKey);	
	Request->SetContentAsString(PostParameters);
	Request->ProcessRequest();
}

void UOWSLoginWidget::OnLoginAndCreateSessionResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			FString ErrorMessage = JsonObject->GetStringField("ErrorMessage");

			if (!ErrorMessage.IsEmpty())
			{
				ErrorLoginAndCreateSession(*ErrorMessage);
				return;
			}

			FString UserSessionGUID = JsonObject->GetStringField("UserSessionGUID");

			NotifyLoginAndCreateSession(UserSessionGUID);
		}
		else
		{
			UE_LOG(OWS, Error, TEXT("OnUserLoginResponseReceived Server returned no data!"));
			ErrorLoginAndCreateSession(TEXT("Unknown login error!"));
		}
	}
	else
	{
		UE_LOG(OWS, Error, TEXT("OnUserLoginResponseReceived Error accessing login server!"));
		ErrorLoginAndCreateSession(TEXT("Unknown error connecting to server!"));
	}
}




void UOWSLoginWidget::OpenCreateAccountInBrowser()
{
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("RPGAPICustomerKey"),
		RPGAPICustomerKey,
		GGameIni
	);

	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("RPGAPIPath"),
		RPGAPIPath,
		GGameIni
	);

	FString TheURL = "http://" + RPGAPIPath + "/Login/CreateAccount/" + RPGAPICustomerKey;
	FPlatformProcess::LaunchURL(*TheURL, nullptr, nullptr);
}