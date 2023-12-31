// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Combat : ModuleRules
{
	public Combat(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });

        PrivateDependencyModuleNames.AddRange(new string[] {
            "AIModule",

            "GameplayTags",
            "GameplayTasks",
            "GameplayAbilities"
        });

        PrivateIncludePaths.AddRange(new string[]{
            "Combat"
        });
    }
}
