// Shoot Them Up Game. All rights reserved.

#include "STUGameModeBase.h"

void ASTUGameModeBase::BeginPlay()
{
	int32 Variable = 0;
	if (Variable < 20)
	{
		for (int32 i = 0; i < 10; ++i)
		{
			UE_LOG(LogTemp, Display, TEXT("Index: %i"), i);
		}
	}
}