// Gangland


#include "Player/GGPlayerController.h"

#include "GGBaseCharacter.h"
#include "GGHealthComponent.h"
#include "GGSpectator.h"

DEFINE_LOG_CATEGORY_STATIC(FLogCategoryLogPlayerController, All, All);

AGGPlayerController::AGGPlayerController(const FObjectInitializer& ObjectInitializer)
{
	
}

void AGGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	/* Возможно ли получать подконтрольного персонажа в Player Controller? */
	AsyncTask(ENamedThreads::GameThread, [this]()
	{
		auto const Current_Character = Cast<AGGBaseCharacter>(GetCharacter());
		if(Current_Character)
		{
			UE_LOG(FLogCategoryLogPlayerController, Display, TEXT("Player %s is Valid"), *Current_Character->GetName());
			Current_Character->GetHealthComponent()->OnDeathEvent.AddUObject(this, &AGGPlayerController::OnDeath);
		}
	});
}

void AGGPlayerController::OnDeath()
{
	if (HasAuthority())
	{
		//PlayerState->SetIsSpectator(true);
		// avoid repeated calls on the server
		
		UE_LOG(FLogCategoryLogPlayerController, Display, TEXT("Player %s is SPECTATING!"), *GetName());
		if (GetRemoteRole() == ROLE_AutonomousProxy)
		{
			//Не разобрался, как работать с дефолтным Спектейтором
			//ChangeState(NAME_Spectating);
			//ClientGotoState(NAME_Spectating);
			
			Possess(GetWorld()->SpawnActor<AGGSpectator>(
				 AcknowledgedPawn->GetActorLocation(),
				 AcknowledgedPawn->GetActorRotation()));
		}
	}
}