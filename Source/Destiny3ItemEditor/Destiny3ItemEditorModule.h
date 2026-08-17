// Copyright Looter Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class IAssetTypeActions;

/**
 *  Editor module for the Looter item system
 *  Registers asset type actions, factories, and a toolbar button for item/perk/stat creation
 */
class FDestiny3ItemEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

	/** Registers the toolbar button and menu entries */
	void RegisterMenus();

	/** Called when the toolbar button is clicked — opens the Item Browser EUW */
	void OnOpenItemBrowser();

	/** Registered asset type actions to clean up on shutdown */
	TArray<TSharedPtr<IAssetTypeActions>> RegisteredAssetActions;
};
