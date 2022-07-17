// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SteamV427 : ModuleRules
{
	public SteamV427(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });

		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"OnlineSubsystem", "OnlineSubsystemNull", "OnlineSubsystemSteam", "OnlineSubsystemUtils"
			}
		);
	}
}
