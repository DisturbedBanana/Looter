#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class IAssetTypeActions;

/**
 *  Editor module for the Looter item system
 *  Registers asset type actions and factories for item/perk/stat creation
 */
class FDestiny3ItemEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

	/** Registered asset type actions to clean up on shutdown */
	TArray<TSharedPtr<IAssetTypeActions>> RegisteredAssetActions;
};
