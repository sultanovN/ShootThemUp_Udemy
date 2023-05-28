// Shoot Them Up Game. All rights reserved.


#include "Components/STUAIPerceptionComponent.h"
#include "STUAIController.h"
#include "Components/STUHealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "STUUtils.h"

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

		const auto PerceivePawn = Cast<APawn>(PerceiveActor);
		const auto AreEnemies = PerceivePawn && STUUtils::AreEnemies(Controller, PerceivePawn->Controller);

		if (EnemyHealthComponent && !EnemyHealthComponent->IsDead() && AreEnemies)
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
