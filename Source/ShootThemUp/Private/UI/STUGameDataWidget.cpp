// Shoot Them Up Game. All rights reserved.


#include "UI/STUGameDataWidget.h"
#include "STUGameModeBase.h"
#include "Player/STUPlayerState.h"

int32 USTUGameDataWidget::GetRoundTime() const
{
	const auto GameMode = GetSTUGameMode();
	return GameMode ? GameMode->GetRoundTime() : -1;
}

int32 USTUGameDataWidget::GetCurrentRound() const
{
	const auto GameMode = GetSTUGameMode();
	return GameMode ? GameMode->GetCurrentRound() : -1;
}

int32 USTUGameDataWidget::GetTotalRoundsNum() const
{
	const auto GameMode = GetSTUGameMode();
	return GameMode ? GameMode->GetGameData().RoundsNum : -1;
}

int32 USTUGameDataWidget::GetKillsNum() const
{
	const auto PlayerState = GetSTUPlayerState();
	return PlayerState ? PlayerState->GetKillsNum() : -1;
}

ASTUGameModeBase* USTUGameDataWidget::GetSTUGameMode() const
{
	return GetWorld() ? Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ASTUPlayerState* USTUGameDataWidget::GetSTUPlayerState() const
{
	return GetOwningPlayer() ? Cast<ASTUPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
