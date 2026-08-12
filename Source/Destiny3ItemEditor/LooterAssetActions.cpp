// Copyright Looter Project. All Rights Reserved.

#include "LooterAssetActions.h"
#include "Items/LooterItemDefinition.h"
#include "Items/LooterPerkDefinition.h"
#include "Items/LooterStatDefinition.h"

// ---- Item Actions ----

FText FLooterItemActions::GetName() const
{
	return NSLOCTEXT("LooterEditor", "ItemActionsName", "Looter Item Definition");
}

FColor FLooterItemActions::GetTypeColor() const
{
	return FColor(255, 195, 0); // Gold
}

UClass* FLooterItemActions::GetSupportedClass() const
{
	return ULooterItemDefinition::StaticClass();
}

uint32 FLooterItemActions::GetCategories()
{
	return EAssetTypeCategories::Gameplay;
}

// ---- Perk Actions ----

FText FLooterPerkActions::GetName() const
{
	return NSLOCTEXT("LooterEditor", "PerkActionsName", "Looter Perk Definition");
}

FColor FLooterPerkActions::GetTypeColor() const
{
	return FColor(0, 180, 255); // Blue
}

UClass* FLooterPerkActions::GetSupportedClass() const
{
	return ULooterPerkDefinition::StaticClass();
}

uint32 FLooterPerkActions::GetCategories()
{
	return EAssetTypeCategories::Gameplay;
}

// ---- Stat Actions ----

FText FLooterStatActions::GetName() const
{
	return NSLOCTEXT("LooterEditor", "StatActionsName", "Looter Stat Definition");
}

FColor FLooterStatActions::GetTypeColor() const
{
	return FColor(0, 200, 100); // Green
}

UClass* FLooterStatActions::GetSupportedClass() const
{
	return ULooterStatDefinition::StaticClass();
}

uint32 FLooterStatActions::GetCategories()
{
	return EAssetTypeCategories::Gameplay;
}
