using UnrealBuildTool;

public class Chessy : ModuleRules
{
	public Chessy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[] {
			"Chessy",
		});

		PublicDependencyModuleNames.AddRange(new string[] {
            // Gameplay Abilities
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			// Custom Shader Location
			"RHI",
			"RenderCore",
			// 
			"Json",
			"JsonUtilities",
			// Defaults
			"Core",
			"CoreUObject",
			"Engine",
			"MoviePlayer",
			"InputCore",
			"HeadMountedDisplay",
			"NavigationSystem",
			"AIModule",
			"UMG",
			"Slate",
			"SlateCore",

			"Gamekit"
		});
    }
}
