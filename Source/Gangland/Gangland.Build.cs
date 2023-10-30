// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Gangland : ModuleRules
{
    public Gangland(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {

        });

        PublicIncludePaths.AddRange(new string[]
        {
            "Gangland/Public/Player",
            "Gangland/Public/Components",
            "Gangland/Public/Dev",
            "Gangland/Public/Weapon",
            "Gangland/Public/UI"
        });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
