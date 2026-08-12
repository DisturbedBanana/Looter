// Copyright Looter Project. All Rights Reserved.

#include "Destiny3ItemEditorModule.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "LooterAssetActions.h"

#define LOCTEXT_NAMESPACE "FDestiny3ItemEditorModule"

void FDestiny3ItemEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	// Register asset type actions for each Looter data asset type
	TSharedRef<IAssetTypeActions> ItemActions = MakeShared<FLooterItemActions>();
	AssetTools.RegisterAssetTypeActions(ItemActions);
	RegisteredAssetActions.Add(ItemActions);

	TSharedRef<IAssetTypeActions> PerkActions = MakeShared<FLooterPerkActions>();
	AssetTools.RegisterAssetTypeActions(PerkActions);
	RegisteredAssetActions.Add(PerkActions);

	TSharedRef<IAssetTypeActions> StatActions = MakeShared<FLooterStatActions>();
	AssetTools.RegisterAssetTypeActions(StatActions);
	RegisteredAssetActions.Add(StatActions);
}

void FDestiny3ItemEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (const TSharedPtr<IAssetTypeActions>& Action : RegisteredAssetActions)
		{
			AssetTools.UnregisterAssetTypeActions(Action.ToSharedRef());
		}
	}
	RegisteredAssetActions.Empty();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDestiny3ItemEditorModule, Destiny3ItemEditor)
