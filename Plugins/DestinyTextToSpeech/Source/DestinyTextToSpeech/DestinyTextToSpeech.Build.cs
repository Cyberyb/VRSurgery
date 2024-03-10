// Some copyright should be here...

using UnrealBuildTool;
using System.IO;

public class DestinyTextToSpeech : ModuleRules
{
	//Return module path
	private string ModulePath
	{
		get
		{
			return ModuleDirectory;
		}
	}
	private string ThirdPartyPath
	{
		get
		{
			return Path.GetFullPath(Path.Combine(ModulePath, "../ThirdParty/dll/Win64/"));
		}
	}
	
	public void LoadDestinyTextToSpeechLib()
	{
		//延迟加载 DLL
		PublicDelayLoadDLLs.Add("TextToSpeechLibrary.dll");
		//运行时依赖
		RuntimeDependencies.Add(Path.Combine(ThirdPartyPath, "TextToSpeechLibrary.dll"));
		RuntimeDependencies.Add("$(TargetOutputDir)/TextToSpeechLibrary.dll", Path.Combine(ThirdPartyPath, "TextToSpeechLibrary.dll"));
		
		//RuntimeDependencies.Add("$(TargetOutputDir)/TextToSpeechLibrary.dll", Path.Combine(PluginDirectory, "Source/ThirdParty/dll/Win64/TextToSpeechLibrary.dll"));
		return;
	}

	
	
	
	public DestinyTextToSpeech(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core", "CoreUObject", "Engine", "InputCore",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			/*
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "../ThirdParty/include"));
		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../ThirdParty/lib/Windows/sapi.lib"));
		}
		bEnableUndefinedIdentifierWarnings = false;
		bEnableExceptions = true;
		bUseRTTI = true;
		*/
			/*
			bEnableUndefinedIdentifierWarnings = false;
			bEnableExceptions = true;
			bUseRTTI = true;
			*/
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		LoadDestinyTextToSpeechLib();//load lib
	}
}
