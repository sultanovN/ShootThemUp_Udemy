// Shoot Them Up Game. All rights reserved.


#include "Player/STUPlayerController.h"
#include "Components/STURespawnComponent.h"
#include "STUGameModeBase.h"

ASTUPlayerController::ASTUPlayerController()
{
	STURespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("STURespawnComponent");
}

void ASTUPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode) { GameMode->OnMatchStateChanged.AddUObject(this, &ASTUPlayerController::OnMatchStateChanged); }
	}
}

void ASTUPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent) return;

	InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASTUPlayerController::OnPauseGame);
}

void ASTUPlayerController::OnPauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
	if (!IsGamePaused)
	{
		IsGamePaused = true;
		GetWorld()->GetAuthGameMode()->SetPause(this);
	}
	else 
	{
		IsGamePaused = false;
		GetWorld()->GetAuthGameMode()->ClearPause();
	}
}

void ASTUPlayerController::OnMatchStateChanged(ESTUMatchState State) 
{
	if (State == ESTUMatchState::InProgress) 
	{ 
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else 
	{ 
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
	
}
