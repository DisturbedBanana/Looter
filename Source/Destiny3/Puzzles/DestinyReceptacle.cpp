#include "DestinyReceptacle.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../Destiny3Character.h"

ADestinyReceptacle::ADestinyReceptacle()
{
	PrimaryActorTick.bCanEverTick = false;

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	RootComponent = OverlapSphere;
	OverlapSphere->InitSphereRadius(150.f);
	OverlapSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	ReceptacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ReceptacleMesh"));
	ReceptacleMesh->SetupAttachment(RootComponent);
	ReceptacleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ADestinyReceptacle::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &ADestinyReceptacle::OnOverlapBegin);
	}
}

void ADestinyReceptacle::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADestiny3Character* Character = Cast<ADestiny3Character>(OtherActor))
	{
		// We'll check if the character is carrying a relic in Blueprints or here once we add the function
		// For now we assume if we overlap and they have it, they can deposit
		if (Character->IsCarryingRelic())
		{
			Character->DepositRelic();
			
			OnRelicDeposited.Broadcast(Character);
			BP_OnRelicDeposited(Character);
		}
	}
}
