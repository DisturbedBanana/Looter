// Copyright Looter Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LooterStatDefinition.generated.h"

/**
 *  Defines a stat type that can appear on loot items (e.g. Impact, Range, Stability)
 *  Create these as Data Assets and reference them from Item Definitions
 */
UCLASS(BlueprintType)
class DESTINY3_API ULooterStatDefinition : public UDataAsset
{
	GENERATED_BODY()

public:

	/** Display name of this stat */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	FText StatName;

	/** Description of what this stat affects */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat", meta = (MultiLine = true))
	FText Description;

	/** Icon displayed next to this stat */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	TObjectPtr<UTexture2D> Icon;

	/** Default minimum value when adding this stat to a new item */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults", meta = (ClampMin = 0, ClampMax = 100))
	int32 DefaultMinValue = 0;

	/** Default maximum value when adding this stat to a new item */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults", meta = (ClampMin = 0, ClampMax = 100))
	int32 DefaultMaxValue = 100;
};
