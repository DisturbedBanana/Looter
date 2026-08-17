// Copyright Looter Project. All Rights Reserved.

using UnrealBuildTool;

public class Destiny3ItemEditor : ModuleRules
{
	public Destiny3ItemEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"Destiny3"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"UnrealEd",
			"AssetTools",
			"AssetRegistry",
			"Slate",
			"SlateCore",
			"InputCore",
			"ToolMenus",
			"Blutility",
			"UMG",
			"UMGEditor"
		});
	}
}
