#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "LooterFactories.generated.h"

/** Factory for creating Looter Item Definition assets via Content Browser */
UCLASS()
class ULooterItemFactory : public UFactory
{
	GENERATED_BODY()

public:
	ULooterItemFactory();
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

/** Factory for creating Looter Perk Definition assets via Content Browser */
UCLASS()
class ULooterPerkFactory : public UFactory
{
	GENERATED_BODY()

public:
	ULooterPerkFactory();
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

/** Factory for creating Looter Stat Definition assets via Content Browser */
UCLASS()
class ULooterStatFactory : public UFactory
{
	GENERATED_BODY()

public:
	ULooterStatFactory();
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
