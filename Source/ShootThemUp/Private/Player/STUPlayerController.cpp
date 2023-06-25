// Shoot Them Up Game. All rights reserved.


#include "Player/STUPlayerController.h"
#include "Components/STURespawnComponent.h"

ASTUPlayerController::ASTUPlayerController()
{
	STURespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("STURespawnComponent");
}
