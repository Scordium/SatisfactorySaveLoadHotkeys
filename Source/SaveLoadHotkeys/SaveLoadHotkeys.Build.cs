using UnrealBuildTool;
using System.IO;
using System;

public class SaveLoadHotkeys : ModuleRules
{
    public SaveLoadHotkeys(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new[] {
            "Core", "CoreUObject",
            "Engine",
            "DeveloperSettings",
            "PhysicsCore",
            "InputCore",
            "CoreOnline",
            "GeometryCollectionEngine",
            "ChaosSolverEngine",
            "AnimGraphRuntime",
            "AssetRegistry",
            "NavigationSystem",
            "AIModule",
            "GameplayTasks",
            "SlateCore", "Slate", "UMG",
            "RenderCore",
            "CinematicCamera",
            "Foliage",
            "EnhancedInput",
            "NetCore",
            "GameplayTags",
        });

        // Header stubs
        PublicDependencyModuleNames.AddRange(new[] {
            "DummyHeaders",
        });

        if (Target.Type == TargetRules.TargetType.Editor) {
            PublicDependencyModuleNames.AddRange(new string[] {"OnlineBlueprintSupport", "AnimGraph"});
        }
        PublicDependencyModuleNames.AddRange(new string[] {"FactoryGame", "SML"});
    }
}