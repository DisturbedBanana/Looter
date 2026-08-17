#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestinyRelic.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class ADestiny3Character;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRelicPickedUp, ADestiny3Character*, Picker);

UCLASS()
class DESTINY3_API ADestinyRelic : public AActor
{
	GENERATED_BODY()
	
public:	
	ADestinyRelic();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* OverlapSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* RelicMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Relic")
	float DeathTimerDuration;

	UPROPERTY(BlueprintAssignable, Category = "Relic")
	FOnRelicPickedUp OnRelicPickedUp;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent, Category = "Relic")
	void BP_OnPickedUp(ADestiny3Character* Picker);
};
