#include "LooterFactories.h"
#include "Items/LooterItemDefinition.h"
#include "Items/LooterPerkDefinition.h"
#include "Items/LooterStatDefinition.h"

// ---- Item Factory ----

ULooterItemFactory::ULooterItemFactory()
{
	SupportedClass = ULooterItemDefinition::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* ULooterItemFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<ULooterItemDefinition>(InParent, Class, Name, Flags);
}

// ---- Perk Factory ----

ULooterPerkFactory::ULooterPerkFactory()
{
	SupportedClass = ULooterPerkDefinition::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* ULooterPerkFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<ULooterPerkDefinition>(InParent, Class, Name, Flags);
}

// ---- Stat Factory ----

ULooterStatFactory::ULooterStatFactory()
{
	SupportedClass = ULooterStatDefinition::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* ULooterStatFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<ULooterStatDefinition>(InParent, Class, Name, Flags);
}
