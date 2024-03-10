// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include <string>
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DestinyTextToSpeechBPLibrary.generated.h"



UENUM()
enum EOperationEnum
{
	Pause,
	Resume,
	StopAll,
	Dispose,
};



UCLASS()
class UDestinyTextToSpeechBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()


	
	/**
	 * 初始化语音朗读功能
	 * by destiny site:https://destiny.cool
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "语音朗读初始化", Keywords = "TextToSpeech"), Category = "TTS")
	static bool DestinyInitSpeech();

	/**
	 * 返回所有安装的语音合成（文字到语音）语音。
	 * by destiny site:https://destiny.cool
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "返回所有安装的语音合成", Keywords = "TextToSpeech"), Category = "TTS")
	static TArray<FString> DestinyGetInstalledVoices();
	
	/**
	 * 异步语音朗读，调用win系统讲述人
	 * @brief
	 * @param SpeechType 朗读的类型 AsyncSpeech异步朗读,SynchronousSpeech同步朗读
	 * @param DataText 需要朗读的文本
	 * @param Volume 语音的音量
	 * @param Voice 发言人 例如 Huihui
	 * @param Rate 播放速率
	 * @param Success 是否成功
	 *  by destiny site:https://destiny.cool
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "语音朗读", Keywords = "TextToSpeech"), Category = "TTS")
	static void DestinyTextToSpeech(FString DataText,FString Voice,int Volume,int Rate,bool& Success);

	/**
	 * 操作语音朗读
	* @param Operation  Pause暂停,Resume继续,StopAll全部停止,Dispose彻底释放语音组件(慎重),
	* by destiny site:https://destiny.cool
	 */
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "语音操作", Keywords = "TextToSpeech"), Category = "TTS")
	static bool DestinyOperationSpeech (EOperationEnum Operation);

	/**
	 * 支持中文编码的base64解码
	 * by destiny site:https://destiny.cool
	 **/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "base64解码", Keywords = "TextToSpeech"), Category = "Base64Utils")
	static FString DestinyDecode(FString Data );
	/**
	 * 支持中文编码的base64解码
	 * by destiny site:https://destiny.cool
	 **/
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "base64编码", Keywords = "TextToSpeech"), Category = "Base64Utils")
	static FString DestinyEncode(FString Data );

private:
	static bool InitDllRunPath();
};
