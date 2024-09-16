// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ObstacleAssault : ModuleRules
{
    public ObstacleAssault(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        // List of public dependencies required by this module
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        if (Target.Type == TargetType.Editor)
        {
            // List of private dependencies for the Editor target
            PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "AutomationController", "FunctionalTesting" });
        }

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
