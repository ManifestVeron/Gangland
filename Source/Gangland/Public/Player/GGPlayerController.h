// Gangland

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GANGLAND_API AGGPlayerController : public APlayerController
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

	AGGPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
protected:

	virtual void BeginPlay() override;

private:

	void OnDeath();
	
	//=================//
	//	FUNCTIONS END
};
