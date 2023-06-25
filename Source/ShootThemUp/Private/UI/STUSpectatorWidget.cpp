// Shoot Them Up Game. All rights reserved.


#include "UI/STUSpectatorWidget.h"
#include "Components/STURespawnComponent.h"

bool USTUSpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
	const auto RespawnComponent = GetOwningPlayer()->FindComponentByClass<USTURespawnComponent>();
	if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

	CountDownTime = RespawnComponent->GetRespawnCountDown();
	return true;
}
