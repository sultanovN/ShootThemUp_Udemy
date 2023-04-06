// Shoot Them Up Game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<ASTUBaseWeapon> WeaponClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UAnimMontage* ReloadAnimMontage;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTUWeaponComponent();
	void SpawnWeapons();

	void StartFire();
	void StopFire();
	void NextWeapon();
	void Reload();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

private:
	UPROPERTY()
	ASTUBaseWeapon* CurrentWeapon;

	UPROPERTY()
	TArray<ASTUBaseWeapon*> Weapons;

	int32 CurrentWeaponIndex = 0;

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	bool EquipAnimProgress = false;
	bool ReloadAnimProgress = false;

	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void EquipWeapon(int32 WeaponIndex);
	void PlayAnimMontage(UAnimMontage* Animation);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
	void OnReloadFinished(USkeletalMeshComponent* MeshComponent);
	bool CanFire() const;
	bool CanEquip() const;
	bool CanReload() const;

	template <typename T> 
	T* FindNotifyByClass(UAnimSequenceBase* Animation) 
	{
		if (!Animation) return nullptr;
		const auto NotifyEvents = Animation->Notifies;
		for (auto NotifyEvent : NotifyEvents)
		{
			auto AnimNotify = Cast<T>(NotifyEvent.Notify);
			if (AnimNotify) 
			{ 
				return AnimNotify;
			}
		}
		return nullptr;
	}
};
