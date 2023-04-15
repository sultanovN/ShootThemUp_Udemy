// Shoot Them Up Game. All rights reserved.


#include "Pickups/STUBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

ASTUBasePickup::ASTUBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(50.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

void ASTUBasePickup::BeginPlay()
{
	Super::BeginPlay();
	
	check(CollisionComponent);

	GenerateRotationYaw();
}

void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
	for (const auto OverlappingPawn: OverlappingPawns) 
	{
		if (GivePickupTo(OverlappingPawn))
		{
			PickupWasTaken();
			break;
		}
	}
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor) 
{
	Super::NotifyActorBeginOverlap(OtherActor);
	const auto Pawn = Cast<APawn>(OtherActor);
	if (GivePickupTo(Pawn)) { PickupWasTaken(); }
	else if (Pawn) { OverlappingPawns.Add(Pawn); }
}

void ASTUBasePickup::NotifyActorEndOverlap(AActor* OtherActor) 
{
	Super::NotifyActorEndOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	OverlappingPawns.Remove(Pawn);
}


void ASTUBasePickup::PickupWasTaken() 
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	if (GetRootComponent()) { GetRootComponent()->SetVisibility(false, true); }
	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUBasePickup::Respawn, RespawnTime);
}
void ASTUBasePickup::Respawn() 
{
	GenerateRotationYaw();
	if (GetRootComponent()) { GetRootComponent()->SetVisibility(true, true); }
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

bool ASTUBasePickup::GivePickupTo(APawn* PlayerPawn)
{
	return false;
}

void ASTUBasePickup::GenerateRotationYaw() 
{
	const auto Direction = FMath::RandBool() ? 1.0f : - 1.0f;
	RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}
