// Shoot Them Up Game. All rights reserved.


#include "Player/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUPlayerState, All, All);

void ASTUPlayerState::LogInfo() 
{
	UE_LOG(LogSTUPlayerState, Display, TEXT("TeamID: %i| K/D: %i/%i"), TeamID, KillsNum, DeathsNum);
}
