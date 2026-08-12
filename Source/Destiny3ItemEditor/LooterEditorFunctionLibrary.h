#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Items/LooterTypes.h"
#include "LooterEditorFunctionLibrary.generated.h"

class ULooterItemDefinition;
class ULooterPerkDefinition;
class ULooterStatDefinition;

/**
 *  Blueprint Function Library for the Looter Item Editor
 *  Provides helper functions used by the Item Browser Editor Utility Widget
 */
UCLASS()
class ULooterEditorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	// ---- Asset Queries ----

	/** Get all Looter Item Definitions from the Asset Registry */
	UFUNCTION(BlueprintCallable, Category = "Looter Editor")
	static TArray<ULooterItemDefinition*> GetAllItemDefinitions();

	/** Get all Looter Perk Definitions from the Asset Registry */
	UFUNCTION(BlueprintCallable, Category = "Looter Editor")
	static TArray<ULooterPerkDefinition*> GetAllPerkDefinitions();

	/** Get all Looter Stat Definitions from the Asset Registry */
	UFUNCTION(BlueprintCallable, Category = "Looter Editor")
	static TArray<ULooterStatDefinition*> GetAllStatDefinitions();

	// ---- Filtering ----

	/** Filter items by search text and optionally by rarity */
	UFUNCTION(BlueprintCallable, Category = "Looter Editor")
	static TArray<ULooterItemDefinition*> FilterItems(
		const TArray<ULooterItemDefinition*>& Items,
		const FString& SearchText,
		ELooterRarity RarityFilter,
		bool bFilterByRarity);

	// ---- Asset Creation ----

	/* Create a new Item Definition asset at the specified content path, with display name auto-set */
	UFUNCTION(BlueprintCallable, Category = "Looter Editor")
	static ULooterItemDefinition* CreateNewItemDefinition(const FString& AssetName, const FString& PackagePath);

	/* Create a new Perk Definition asset at the specified content path */
	UFUNCTION(BlueprintCallable, Category = "Looter Editor")
	static ULooterPerkDefinition* CreateNewPerkDefinition(const FString& AssetName, const FString& PackagePath);

	/* Create a new Stat Definition asset at the specified content path */
	UFUNCTION(BlueprintCallable, Category = "Looter Editor")
	static ULooterStatDefinition* CreateNewStatDefinition(const FString& AssetName, const FString& PackagePath);

	// ---- Editor Interaction ----

	/* Open an asset in the editor's Details panel */
	UFUNCTION(BlueprintCallable, Category = "Looter Editor")
	static void OpenAssetInEditor(UObject* Asset);

	/* Save an asset to disk */
	UFUNCTION(BlueprintCallable, Category = "Looter Editor")
	static void SaveAsset(UObject* Asset);

	// ---- Display Helpers ----

	/* Get the display color for a rarity tier (Destiny-style colors) */
	UFUNCTION(BlueprintPure, Category = "Looter Editor")
	static FLinearColor GetRarityColor(ELooterRarity Rarity);

	/* Get the display name for a rarity tier */
	UFUNCTION(BlueprintPure, Category = "Looter Editor")
	static FText GetRarityDisplayName(ELooterRarity Rarity);
};
