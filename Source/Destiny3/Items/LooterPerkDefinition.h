// Copyright Looter Project. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LooterPerkDefinition.generated.h"

/** Type of perk slot */
UENUM(BlueprintType)
enum class ELooterPerkType : uint8
{
	Intrinsic   UMETA(DisplayName = "Intrinsic"),
	Trait       UMETA(DisplayName = "Trait"),
	Mod         UMETA(DisplayName = "Mod")
};

/**
 *  Defines a perk that can appear on loot items (e.g. Outlaw, Kill Clip, Rampage)
 *  Create these as Data Assets and add them to Item Definition perk columns
 */
UCLASS(BlueprintType)
class DESTINY3_API ULooterPerkDefinition : public UDataAsset
{
	GENERATED_BODY()

public:

	/** Display name of this perk */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Perk")
	FText PerkName;

	/** Description of what this perk does */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Perk", meta = (MultiLine = true))
	FText Description;

	/** Icon displayed for this perk */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Perk")
	TObjectPtr<UTexture2D> Icon;

	/** What type of perk slot this occupies */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Perk")
	ELooterPerkType PerkType = ELooterPerkType::Trait;
};
