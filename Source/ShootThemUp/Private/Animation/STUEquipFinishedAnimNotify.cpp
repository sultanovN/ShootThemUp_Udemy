// Shoot Them Up Game. All rights reserved.


#include "Animation/STUEquipFinishedAnimNotify.h"

void USTUEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) 
{
	OnNotified.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}
