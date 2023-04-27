// Shoot Them Up Game. All rights reserved.


#include "AI/STUAICharacter.h"
#include "AI/STUAIController.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjInit) : Super(ObjInit) 
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ASTUAIController::StaticClass();
}
