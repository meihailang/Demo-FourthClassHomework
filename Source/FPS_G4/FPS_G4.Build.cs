// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FPS_G4 : ModuleRules
{
	public FPS_G4(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "MoviePlayer","UMG" });
	}
}
