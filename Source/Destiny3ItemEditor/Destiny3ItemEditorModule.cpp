// Copyright Looter Project. All Rights Reserved.

#include "Destiny3ItemEditorModule.h"
#include "AssetToolsModule.h"
#include "IAssetTools.h"
#include "LooterAssetActions.h"
#include "ToolMenus.h"
#include "Editor.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "Styling/AppStyle.h"

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

	// Register toolbar button (deferred until menus are ready)
	UToolMenus::RegisterStartupCallback(
		FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FDestiny3ItemEditorModule::RegisterMenus)
	);
}

void FDestiny3ItemEditorModule::ShutdownModule()
{
	// Unregister toolbar
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);

	// Unregister asset type actions
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

void FDestiny3ItemEditorModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);

	// In UE5, the main level editor toolbar is 'LevelEditor.LevelEditorToolBar.AssetsToolBar'
	UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.AssetsToolBar");
	if (!ToolbarMenu)
	{
		// Fallback for some UE5 configurations
		ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
	}

	if (ToolbarMenu)
	{
		FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("LooterTools");
		Section.AddEntry(FToolMenuEntry::InitToolBarButton(
			"OpenItemBrowser",
			FUIAction(FExecuteAction::CreateRaw(this, &FDestiny3ItemEditorModule::OnOpenItemBrowser)),
			LOCTEXT("ItemBrowser", "Item Browser"),
			LOCTEXT("ItemBrowserTooltip", "Open the Looter Item Browser to create and manage items, perks, and stats"),
			FSlateIcon(FAppStyle::GetAppStyleSetName(), TEXT("Icons.Package"))
		));
	}
}

void FDestiny3ItemEditorModule::OnOpenItemBrowser()
{
	// Load the Editor Utility Widget Blueprint
	UEditorUtilityWidgetBlueprint* WidgetBP = LoadObject<UEditorUtilityWidgetBlueprint>(
		nullptr,
		TEXT("/Game/EditorTools/EUW_ItemBrowser.EUW_ItemBrowser")
	);

	if (!WidgetBP)
	{
		UE_LOG(LogTemp, Warning, TEXT("Looter: Could not find EUW_ItemBrowser at /Game/EditorTools/EUW_ItemBrowser. Make sure the widget exists."));
		return;
	}

	// Spawn the widget as a dockable editor tab
	if (GEditor)
	{
		UEditorUtilitySubsystem* Subsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
		if (Subsystem)
		{
			Subsystem->SpawnAndRegisterTab(WidgetBP);
		}
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDestiny3ItemEditorModule, Destiny3ItemEditor)
