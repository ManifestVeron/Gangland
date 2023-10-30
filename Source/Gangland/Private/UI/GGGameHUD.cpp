// Gangland


#include "UI/GGGameHUD.h"

#include "Engine/Canvas.h"

void AGGGameHUD::DrawHUD()
{
	Super::DrawHUD();

	DrawCrossHair();
}

void AGGGameHUD::DrawCrossHair()
{
	const TInterval<float> Center(Canvas->SizeX*0.5f,Canvas->SizeY*0.5);

	constexpr float HalfLineSize = 10.0f;
	constexpr float LineThickness = 2.0f;
	const FLinearColor LinearColor = FLinearColor::Red;

	
	DrawLine(Center.Min - HalfLineSize,
		Center.Max,
		Center.Min + HalfLineSize,
		Center.Max,
		LinearColor,
		LineThickness);

	DrawLine(Center.Min,
		Center.Max - HalfLineSize,
		Center.Min,
		Center.Max + HalfLineSize,
		LinearColor,
		LineThickness);
}
