// Gangland


#include "Components/GGCharacterMovementComponent.h"
#include "Player/GGBaseCharacter.h"

float UGGCharacterMovementComponent::GetMaxSpeed() const
{
	const AGGBaseCharacter* Player = Cast<AGGBaseCharacter>(GetPawnOwner());
	const float MaxSpeed = Super::GetMaxSpeed();
	return Player  ? MaxSpeed * RunModifier : MaxSpeed;
}
