// Shoot Them Up Game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUCoreTypes.h"
#include "STUPlayerController.generated.h"

class USTURespawnComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASTUPlayerController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTURespawnComponent* STURespawnComponent;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	bool IsGamePaused = false;
	void OnPauseGame();
	void OnMatchStateChanged(ESTUMatchState State);
};
