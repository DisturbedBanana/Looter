// Copyright Looter Project. All Rights Reserved.

#include "Items/LooterItemDefinition.h"

FPrimaryAssetId ULooterItemDefinition::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(TEXT("LooterItem"), GetFName());
}
