// Shoot Them Up Game. All rights reserved.


#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "STUGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUGameHUD, All, All);

void ASTUGameHUD::BeginPlay() 
{
	Super::BeginPlay();

	GameWidgets.Add(ESTUMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
	GameWidgets.Add(ESTUMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(ESTUMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));

	for (auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (!GameWidget) continue;
		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GetWorld()) 
	{ 
		const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode());
		if (GameMode) 
		{ 
			GameMode->OnMatchStateChanged.AddUObject(this, &ASTUGameHUD::OnMatchStateChanged);
		}
	}
}


void ASTUGameHUD::DrawHUD() 
{
	Super::DrawHUD();

	//DrawCrossHair();
}

void ASTUGameHUD::DrawCrossHair() 
{
	const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);
	const float HalfLineSize = 10.0f;
	const float Thickness = 2.0f;
	const FLinearColor Color = FLinearColor::Green;
	DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, Color, Thickness);
	DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, Color, Thickness);
}

void ASTUGameHUD::OnMatchStateChanged(ESTUMatchState State) 
{
	if (CurrentWidget) 
	{ 
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(State)) 
	{ 
		CurrentWidget = GameWidgets[State];
	}

	if (CurrentWidget)
	{ 
		CurrentWidget->SetVisibility(ESlateVisibility::Visible); 
	}

	UE_LOG(LogSTUGameHUD, Display, TEXT("Match State Changed: %s"), *UEnum::GetValueAsString(State));
}
