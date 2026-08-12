// Copyright Looter Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LooterTypes.generated.h"

/** Rarity tiers for loot items, from common to exotic */
UENUM(BlueprintType)
enum class ELooterRarity : uint8
{
	Common      UMETA(DisplayName = "Common"),
	Uncommon    UMETA(DisplayName = "Uncommon"),
	Rare        UMETA(DisplayName = "Rare"),
	Legendary   UMETA(DisplayName = "Legendary"),
	Exotic      UMETA(DisplayName = "Exotic")
};

/** Types of items that can drop as loot */
UENUM(BlueprintType)
enum class ELooterItemType : uint8
{
	// Weapons
	Weapon_AutoRifle        UMETA(DisplayName = "Auto Rifle"),
	Weapon_HandCannon       UMETA(DisplayName = "Hand Cannon"),
	Weapon_PulseRifle       UMETA(DisplayName = "Pulse Rifle"),
	Weapon_ScoutRifle       UMETA(DisplayName = "Scout Rifle"),
	Weapon_Shotgun          UMETA(DisplayName = "Shotgun"),
	Weapon_SniperRifle      UMETA(DisplayName = "Sniper Rifle"),
	Weapon_FusionRifle      UMETA(DisplayName = "Fusion Rifle"),
	Weapon_RocketLauncher   UMETA(DisplayName = "Rocket Launcher"),
	Weapon_Sword            UMETA(DisplayName = "Sword"),
	Weapon_GrenadeLauncher  UMETA(DisplayName = "Grenade Launcher"),

	// Armor
	Armor_Helmet            UMETA(DisplayName = "Helmet"),
	Armor_Gauntlets         UMETA(DisplayName = "Gauntlets"),
	Armor_ChestArmor        UMETA(DisplayName = "Chest Armor"),
	Armor_LegArmor          UMETA(DisplayName = "Leg Armor"),
	Armor_ClassItem         UMETA(DisplayName = "Class Item")
};

/** Defines a rollable stat range on an item */
USTRUCT(BlueprintType)
struct FLooterStatRange
{
	GENERATED_BODY()

	/** Which stat this range is for */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	TObjectPtr<class ULooterStatDefinition> StatDefinition;

	/** Minimum roll value for this stat */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat", meta = (ClampMin = 0, ClampMax = 100))
	int32 MinValue = 0;

	/** Maximum roll value for this stat */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat", meta = (ClampMin = 0, ClampMax = 100))
	int32 MaxValue = 100;
};

/** A column of selectable perks on an item */
USTRUCT(BlueprintType)
struct FLooterPerkColumn
{
	GENERATED_BODY()

	/** Display name for this perk column */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Perks")
	FText ColumnName;

	/** Perks available in this column */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Perks")
	TArray<TObjectPtr<class ULooterPerkDefinition>> Perks;
};
