// Copyright Looter Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LooterTypes.h"
#include "LooterItemDefinition.generated.h"

class ULooterPerkDefinition;
class ULooterStatDefinition;
class AShooterWeapon;

/**
 *  Primary Data Asset that defines a complete loot item (weapon or armor)
 *  Designers create these via Content Browser: Right-click > Gameplay > Looter Item Definition
 *  
 *  Each instance represents a unique item archetype (e.g. "The Last Word", "Gjallarhorn")
 *  with its stat ranges, perk pools, visuals, and lore
 */
UCLASS(BlueprintType)
class DESTINY3_API ULooterItemDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	// ---- Identity ----

	/** Display name shown to players */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Identity")
	FText DisplayName;

	/** Short gameplay description */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Identity", meta = (MultiLine = true))
	FText Description;

	/** Flavor / lore text */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Identity", meta = (MultiLine = true))
	FText LoreText;

	/** Rarity tier of this item */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Identity")
	ELooterRarity Rarity = ELooterRarity::Common;

	/** What type of item this is (weapon subtype or armor slot) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Identity")
	ELooterItemType ItemType = ELooterItemType::Weapon_AutoRifle;

	// ---- Visuals ----

	/** Inventory icon */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals")
	TObjectPtr<UTexture2D> Icon;

	/** 3D mesh for world/inspection view */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Visuals")
	TSoftObjectPtr<UStaticMesh> ItemMesh;

	// ---- Gameplay ----

	/** Weapon actor class to spawn when this item is equipped (weapons only) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay", meta = (EditConditionHides, EditCondition = "ItemType < ELooterItemType::Armor_Helmet"))
	TSubclassOf<AShooterWeapon> WeaponClass;

	/** Base power level of this item */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay", meta = (ClampMin = 0, ClampMax = 2000))
	int32 PowerLevel = 1000;

	// ---- Stats ----

	/** Stat roll ranges for this item */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	TArray<FLooterStatRange> StatRanges;

	// ---- Perks ----

	/** Fixed intrinsic perk (e.g. exotic perk) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Perks")
	TObjectPtr<ULooterPerkDefinition> IntrinsicPerk;

	/** Rollable perk columns — each column has a pool of selectable perks */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Perks")
	TArray<FLooterPerkColumn> PerkColumns;

	// ---- UPrimaryDataAsset Interface ----

	/** Returns a unique identifier for the Asset Manager */
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
