#include "LooterEditorFunctionLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "Editor.h"
#include "FileHelpers.h"
#include "LooterFactories.h"
#include "Items/LooterItemDefinition.h"
#include "Items/LooterPerkDefinition.h"
#include "Items/LooterStatDefinition.h"

// ---- Asset Queries ----

TArray<ULooterItemDefinition*> ULooterEditorFunctionLibrary::GetAllItemDefinitions()
{
	TArray<ULooterItemDefinition*> Result;

	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

	TArray<FAssetData> AssetDataList;
	AssetRegistry.GetAssetsByClass(ULooterItemDefinition::StaticClass()->GetClassPathName(), AssetDataList);

	for (const FAssetData& AssetData : AssetDataList)
	{
		if (ULooterItemDefinition* Item = Cast<ULooterItemDefinition>(AssetData.GetAsset()))
		{
			Result.Add(Item);
		}
	}

	return Result;
}

TArray<ULooterPerkDefinition*> ULooterEditorFunctionLibrary::GetAllPerkDefinitions()
{
	TArray<ULooterPerkDefinition*> Result;

	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

	TArray<FAssetData> AssetDataList;
	AssetRegistry.GetAssetsByClass(ULooterPerkDefinition::StaticClass()->GetClassPathName(), AssetDataList);

	for (const FAssetData& AssetData : AssetDataList)
	{
		if (ULooterPerkDefinition* Perk = Cast<ULooterPerkDefinition>(AssetData.GetAsset()))
		{
			Result.Add(Perk);
		}
	}

	return Result;
}

TArray<ULooterStatDefinition*> ULooterEditorFunctionLibrary::GetAllStatDefinitions()
{
	TArray<ULooterStatDefinition*> Result;

	IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

	TArray<FAssetData> AssetDataList;
	AssetRegistry.GetAssetsByClass(ULooterStatDefinition::StaticClass()->GetClassPathName(), AssetDataList);

	for (const FAssetData& AssetData : AssetDataList)
	{
		if (ULooterStatDefinition* Stat = Cast<ULooterStatDefinition>(AssetData.GetAsset()))
		{
			Result.Add(Stat);
		}
	}

	return Result;
}

// ---- Filtering ----

TArray<ULooterItemDefinition*> ULooterEditorFunctionLibrary::FilterItems(
	const TArray<ULooterItemDefinition*>& Items,
	const FString& SearchText,
	ELooterRarity RarityFilter,
	bool bFilterByRarity)
{
	TArray<ULooterItemDefinition*> Result;

	for (ULooterItemDefinition* Item : Items)
	{
		if (!Item) // null check
		{
			continue;
		}
		
		// rarity arg
		if (bFilterByRarity && Item->Rarity != RarityFilter)
		{
			continue;
		}

		// search args
		if (!SearchText.IsEmpty())
		{
			const FString ItemName = Item->DisplayName.ToString();
			if (!ItemName.Contains(SearchText))
			{
				continue;
			}
		}

		Result.Add(Item);
	}

	return Result;
}

// ---- Asset Creation ----

ULooterItemDefinition* ULooterEditorFunctionLibrary::CreateNewItemDefinition(const FString& AssetName, const FString& PackagePath)
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	ULooterItemFactory* Factory = NewObject<ULooterItemFactory>();
	UObject* NewAsset = AssetTools.CreateAsset(AssetName, PackagePath, ULooterItemDefinition::StaticClass(), Factory);

	ULooterItemDefinition* NewItem = Cast<ULooterItemDefinition>(NewAsset);
	if (NewItem)
	{
		NewItem->DisplayName = FText::FromString(AssetName); // displayname is an immutable FText
		NewItem->MarkPackageDirty();
	}

	return NewItem;
}

ULooterPerkDefinition* ULooterEditorFunctionLibrary::CreateNewPerkDefinition(const FString& AssetName, const FString& PackagePath)
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	ULooterPerkFactory* Factory = NewObject<ULooterPerkFactory>();
	UObject* NewAsset = AssetTools.CreateAsset(AssetName, PackagePath, ULooterPerkDefinition::StaticClass(), Factory);

	return Cast<ULooterPerkDefinition>(NewAsset);
}

ULooterStatDefinition* ULooterEditorFunctionLibrary::CreateNewStatDefinition(const FString& AssetName, const FString& PackagePath)
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	ULooterStatFactory* Factory = NewObject<ULooterStatFactory>();
	UObject* NewAsset = AssetTools.CreateAsset(AssetName, PackagePath, ULooterStatDefinition::StaticClass(), Factory);

	return Cast<ULooterStatDefinition>(NewAsset);
}

// ---- Editor Interaction ----

void ULooterEditorFunctionLibrary::OpenAssetInEditor(UObject* Asset)
{
	if (Asset && GEditor)
	{
		GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->OpenEditorForAsset(Asset);
	}
}

void ULooterEditorFunctionLibrary::SaveAsset(UObject* Asset)
{
	if (Asset)
	{
		TArray<UPackage*> PackagesToSave;
		PackagesToSave.Add(Asset->GetOutermost());
		FEditorFileUtils::PromptForCheckoutAndSave(PackagesToSave, false, false);
	}
}

// ---- Display Helpers ----

FLinearColor ULooterEditorFunctionLibrary::GetRarityColor(ELooterRarity Rarity)
{
	switch (Rarity)
	{
		case ELooterRarity::Common:     return FLinearColor(0.76f, 0.76f, 0.76f, 1.0f);  // Silver/White
		case ELooterRarity::Uncommon:   return FLinearColor(0.19f, 0.77f, 0.26f, 1.0f);  // Green
		case ELooterRarity::Rare:       return FLinearColor(0.20f, 0.53f, 0.92f, 1.0f);  // Blue
		case ELooterRarity::Legendary:  return FLinearColor(0.63f, 0.21f, 0.79f, 1.0f);  // Purple
		case ELooterRarity::Exotic:     return FLinearColor(0.95f, 0.77f, 0.06f, 1.0f);  // Gold
		default:                        return FLinearColor::White;
	}
	// fuck les switchs
}

FText ULooterEditorFunctionLibrary::GetRarityDisplayName(ELooterRarity Rarity)
{
	switch (Rarity)
	{
		case ELooterRarity::Common:     return NSLOCTEXT("Looter", "RarityCommon", "Common");
		case ELooterRarity::Uncommon:   return NSLOCTEXT("Looter", "RarityUncommon", "Uncommon");
		case ELooterRarity::Rare:       return NSLOCTEXT("Looter", "RarityRare", "Rare");
		case ELooterRarity::Legendary:  return NSLOCTEXT("Looter", "RarityLegendary", "Legendary");
		case ELooterRarity::Exotic:     return NSLOCTEXT("Looter", "RarityExotic", "Exotic");
		default:                        return NSLOCTEXT("Looter", "RarityUnknown", "Unknown");
	}
	// fuck les switchs v2
}
