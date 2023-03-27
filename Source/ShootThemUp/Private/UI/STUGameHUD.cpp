// Shoot Them Up Game. All rights reserved.


#include "UI/STUGameHUD.h"
#include "Engine/Canvas.h"

void ASTUGameHUD::DrawHUD() 
{
	Super::DrawHUD();

	DrawCrossHair();
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
