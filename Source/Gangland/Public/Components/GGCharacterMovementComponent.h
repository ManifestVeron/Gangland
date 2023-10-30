// Gangland

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "GGCharacterMovementComponent.generated.h"

/**
 *
 */
UCLASS()
class GANGLAND_API UGGCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
	//	VARIABLES BEGIN
	//=================//
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.5", ClampMax = "10.0"))
	float RunModifier = 2.0f;
	
protected:
	
private:
	
	//=================//
	//	VARIABLES END
	
	//	FUNCTIONS BEGIN
	//=================//
	
public:
	
	virtual float GetMaxSpeed() const override;
	
protected:

private:
	
	//=================//
	//	FUNCTIONS END
};
