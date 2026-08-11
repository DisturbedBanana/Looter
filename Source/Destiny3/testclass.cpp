#include "testclass.h"

#include "Engine/Engine.h"

ATestClass::ATestClass()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATestClass::SetPlaceholderText(const FString& NewText)
{
	PlaceholderText = NewText;
}

void ATestClass::PrintPlaceholderMessage() const
{
	UE_LOG(LogTemp, Log, TEXT("PlaceholderText: %s | PlaceholderFloat: %.2f | PlaceholderInt: %d | Toggle: %s"),
		*PlaceholderText,
		PlaceholderFloat,
		PlaceholderInt,
		bPlaceholderToggle ? TEXT("true") : TEXT("false"));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.0f,
			FColor::Cyan,
			FString::Printf(TEXT("%s | %.2f | %d"), *PlaceholderText, PlaceholderFloat, PlaceholderInt));
	}
}

float ATestClass::GetScaledPlaceholderFloat(float Scale) const
{
	return PlaceholderFloat * Scale;
}
