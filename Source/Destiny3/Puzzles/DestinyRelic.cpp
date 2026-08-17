#include "DestinyRelic.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../Destiny3Character.h"

ADestinyRelic::ADestinyRelic()
{
	PrimaryActorTick.bCanEverTick = false;

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	RootComponent = OverlapSphere;
	OverlapSphere->InitSphereRadius(100.f);
	OverlapSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	RelicMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RelicMesh"));
	RelicMesh->SetupAttachment(RootComponent);
	RelicMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	DeathTimerDuration = 30.0f;
}

void ADestinyRelic::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &ADestinyRelic::OnOverlapBegin);
	}
}

void ADestinyRelic::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ADestiny3Character* Character = Cast<ADestiny3Character>(OtherActor)) //Check if actor is a player character
	{
		// Notify the character that they picked up the relic
		Character->PickUpRelic(DeathTimerDuration);
		
		OnRelicPickedUp.Broadcast(Character);
		BP_OnPickedUp(Character);

		Destroy(); // Or hide and disable, depending on network structure. Let's just destroy for simplicity.
	}
}
