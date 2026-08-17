#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestinyReceptacle.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class ADestiny3Character;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRelicDeposited, ADestiny3Character*, Depositor);

UCLASS()
class DESTINY3_API ADestinyReceptacle : public AActor
{
	GENERATED_BODY()
	
public:	
	ADestinyReceptacle();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* OverlapSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* ReceptacleMesh;

	UPROPERTY(BlueprintAssignable, Category = "Receptacle")
	FOnRelicDeposited OnRelicDeposited;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent, Category = "Receptacle")
	void BP_OnRelicDeposited(ADestiny3Character* Depositor);
};
