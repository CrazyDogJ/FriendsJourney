// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FriendsJourney : ModuleRules
{
	public FriendsJourney(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"UMG",
			"RenderCore",
			"InputCore", 
			"EnhancedInput", 
			"ALS",
			"ALSExtend",
			"SlateCore",
			"Buoyancy",
			"Water",
			"GameplayAbilities",
			"GameplayTags",
			"NetCore",
			"AIModule",
			"PhysicsCore",
			"NavigationSystem", 
			"ChaosVehicles",
			"OverlayMaterialManager"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Minimap", 
			"OnlineSubsystem", 
			"OnlineSubsystemUtils"
		});
		
		DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
	}
}
