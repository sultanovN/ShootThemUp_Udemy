// Shoot Them Up Game. All rights reserved.


#include "Components/STUAIPerceptionComponent.h"
#include "STUAIController.h"
#include "Components/STUHealthComponent.h"
#include "Perception/AISense_Sight.h"


AActor* USTUAIPerceptionComponent::GetClosestEnemy()
{
	TArray<AActor*> PerceiveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);
	if (PerceiveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float ShortestDistanceToEnemy = MAX_FLT;
	AActor* ClosestEnemy = nullptr;

	for (const auto PerceiveActor: PerceiveActors) 
	{
		const auto EnemyHealthComponent = PerceiveActor->FindComponentByClass<USTUHealthComponent>();
		if (EnemyHealthComponent && !EnemyHealthComponent->IsDead())
		{
			const auto CurrentDistance = (PerceiveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < ShortestDistanceToEnemy)
			{
				ShortestDistanceToEnemy = CurrentDistance;
				ClosestEnemy = PerceiveActor;
			}
		}
	}
	return ClosestEnemy;
}
