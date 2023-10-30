// Gangland

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GGGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class GANGLAND_API AGGGameHUD : public AHUD
{
	GENERATED_BODY()
	
	//	VARIABLES BEGIN
	//=================//
	
public:
	
protected:
	
private:

	//=================//
	//	VARIABLES END
	
	//	FUNCTIONS BEGIN
	//=================//
	
public:

	virtual void DrawHUD() override;

protected:

private:
	
	void DrawCrossHair();
	
	//=================//
	//	FUNCTIONS END

};
