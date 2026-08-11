#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "testclass.generated.h"

UCLASS(Blueprintable)
class DESTINY3_API ATestClass : public AActor
{
	GENERATED_BODY()

public:
	ATestClass();

	// Simple placeholder values for editor/Blueprint wiring.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placeholder")
	float PlaceholderFloat = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placeholder")
	int32 PlaceholderInt = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placeholder")
	bool bPlaceholderToggle = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placeholder")
	FString PlaceholderText = TEXT("Hello from TestClass");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Placeholder TEST NEW SECTION FOR BUILD")
	FString NewSectionText = TEXT("Hello from New Section");

	UFUNCTION(BlueprintCallable, Category = "Placeholder")
	void SetPlaceholderText(const FString& NewText);

	UFUNCTION(BlueprintCallable, Category = "Placeholder")
	void PrintPlaceholderMessage() const;

	UFUNCTION(BlueprintPure, Category = "Placeholder")
	float GetScaledPlaceholderFloat(float Scale) const;
};

