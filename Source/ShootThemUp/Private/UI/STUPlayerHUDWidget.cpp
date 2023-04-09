// Shoot Them Up Game. All rights reserved.


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
	auto const Player = GetOwningPlayerPawn();
	if (!Player) return 0.0f;

	auto Component = Player->GetComponentByClass(USTUHealthComponent::StaticClass());
	auto HealthComponent = Cast<USTUHealthComponent>(Component);
	if (!HealthComponent) return 0.0f;
	return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const 
{
	auto const Player = GetOwningPlayerPawn();
	if (!Player) return false;

	auto Component = Player->GetComponentByClass(USTUWeaponComponent::StaticClass());
	auto WeaponComponent = Cast<USTUWeaponComponent>(Component);
	if (!WeaponComponent) return false;
	return WeaponComponent->GetWeaponUIData(UIData);
}
