// Copyright Epic Games, Inc. All Rights Reserved.





#include "DestinyTextToSpeechBPLibrary.h"
#include "DestinyTextToSpeech.h"
#include "Engine.h"
#include "Misc/Paths.h"

#include "Misc/Base64.h"
#include <iostream> 
#include <string>
using namespace std;

typedef char* (*DLLCharType)(char* ParameterText,char* Voice,int Volume,int Rate);
typedef bool* (*DLLCharType2)();
typedef bool* (*DLLCharType3)(int Opt);
typedef char* (*DLLCharType4)();


static void* DLLHandle = nullptr;
static FString FileStaticPath;
static bool InitComplete = false;


UDestinyTextToSpeechBPLibrary::UDestinyTextToSpeechBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FString UDestinyTextToSpeechBPLibrary::DestinyEncode(FString Data)
{
	TArray<uint8> content;
	std::string _s(TCHAR_TO_UTF8(*Data));
	content.Append((unsigned char *)_s.data(), _s.size());
	return FBase64::Encode(content);
}

FString UDestinyTextToSpeechBPLibrary::DestinyDecode(FString Data)
{
	const int32 DataSize = Data.Len();
	uint8* Blob = new uint8[DataSize];
	FString::ToHexBlob(Data, Blob, DataSize);
	FString centerBase64 = BytesToString(Blob, DataSize);
	TArray<uint8> content;
	FBase64::Decode(Data, content);
	const FString RawData = FString(UTF8_TO_TCHAR(content.GetData()));
	return RawData;
}



bool UDestinyTextToSpeechBPLibrary::InitDllRunPath()
{
	//FString Path = "DestinyTextToSpeech/Source/ThirdParty/dll/Win64/TextToSpeechLibrary.dll";
	FString FilePath = FPaths::Combine(*FPaths::ProjectPluginsDir(), TEXT("DestinyTextToSpeech/Source/ThirdParty/dll/Win64/"), TEXT("TextToSpeechLibrary.dll"));
	if (FPaths::FileExists(FilePath))
	{
		FileStaticPath = FilePath;
		DLLHandle = FPlatformProcess::GetDllHandle(*FilePath);
		InitComplete = true;
		return true;
	}
	GEngine->AddOnScreenDebugMessage(-1, 10.0, FColor::Red, "Failed to load the class library!");

	return false;
}


bool UDestinyTextToSpeechBPLibrary::DestinyInitSpeech()
{
	if (!InitDllRunPath())
	{
		return false;
	}
	if (DLLHandle != nullptr)
	{
		DLLCharType2 DLLFuncPtr2 = nullptr;
		DLLFuncPtr2 = (DLLCharType2)FPlatformProcess::GetDllExport(DLLHandle, TEXT("DestinyInitSpeech"));
		if(DLLFuncPtr2 != nullptr)
		{
			bool* Result = DLLFuncPtr2();
			if (Result)
			{
				return true;
			}
		}
	}
	return false;
}


bool UDestinyTextToSpeechBPLibrary::DestinyOperationSpeech(EOperationEnum Operation)
{
	if (!InitDllRunPath())
	{
		return false;
	}
	if (DLLHandle != nullptr)
	{
		DLLCharType3 DLLFuncPtr3 = nullptr;
		DLLFuncPtr3 = (DLLCharType3)FPlatformProcess::GetDllExport(DLLHandle, TEXT("DestinyOperationSpeech"));
		if(DLLFuncPtr3 != nullptr)
		{
			int Opt = 0;
			switch (Operation)
			{
				case Pause:
					Opt = 1;
				break;
				case Resume:
					Opt = 2;
				break;
				case StopAll:
					Opt = 3;
				break;
				case Dispose:
					Opt = 4;
				break;
			}
			
			bool* Result = DLLFuncPtr3(Opt);
			if (Result)
			{
				return true;
			}
		}
	}
	return false;
}


TArray<FString> UDestinyTextToSpeechBPLibrary::DestinyGetInstalledVoices()
{
	TArray<FString> ResArray;
	if (!InitDllRunPath())
	{
		return ResArray;
	}
	if (DLLHandle != nullptr)
	{
		DLLCharType4 DLLFuncPtr4 = nullptr;
		DLLFuncPtr4 = (DLLCharType4)FPlatformProcess::GetDllExport(DLLHandle, TEXT("DestinyGetInstalledVoices"));
		if(DLLFuncPtr4 != nullptr)
		{
			char* Result = DLLFuncPtr4();
			FString ResultF(Result);
			ResultF.ParseIntoArray(ResArray,TEXT("||"),true);
		}
	}
	return ResArray;
}


void UDestinyTextToSpeechBPLibrary::DestinyTextToSpeech(FString DataText,FString Voice,int Volume,int Rate,bool& Success)
{

		//void* DLLHandle = FPlatformProcess::GetDllHandle(*FilePath);
		if (DLLHandle != nullptr)
		{
			DLLCharType DLLFuncPtr = nullptr;
			const FString ProcName = "DestinyTextToSpeech";

			DLLFuncPtr = (DLLCharType)FPlatformProcess::GetDllExport(DLLHandle, *ProcName);

			if (DLLFuncPtr != nullptr)
			{


				const FString EncodeData = DestinyEncode(*DataText);
				char* Result = DLLFuncPtr(TCHAR_TO_UTF8(*EncodeData),TCHAR_TO_UTF8(*Voice),Volume,Rate);
				GEngine->AddOnScreenDebugMessage(-1, 10.0, FColor::Red, Result);
				//FPlatformProcess::FreeDllHandle(DLLHandle);
				Success = true;
			}else
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.0, FColor::Red, "DLLFuncPtr is a null pointer!");
				Success = false;
			}
			
		}else
		{
			GEngine->AddOnScreenDebugMessage(-1, 10.0, FColor::Red, "DLLHandle is a null pointer!");
			Success = false;
		}

}

