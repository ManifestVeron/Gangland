// Gangland

#include "Components/GGHealthComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

// Sets default values for this component's properties
UGGHealthComponent::UGGHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
	//SetIsReplicated(true);
	
}

// Called when the game starts
void UGGHealthComponent::BeginPlay()
{
	Super::BeginPlay();
		SetHealth(MaxHealth);

		AActor* ComponentOwner = GetOwner();
		if (ComponentOwner)
		{
			ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UGGHealthComponent::OnTakeDamage);
		}
}

void UGGHealthComponent::OnTakeDamage
(
	AActor* DamagedActor,
	float Damage,
	const class UDamageType* DamageType,
	class AController* InstigatedBy,
	AActor* DamageCauser
	)
{
	if (Damage <= 0.0f || IsDead() ||  !GetWorld())
	{
		return;
	}

	SetHealth(Health - Damage);

	GetWorld()->GetTimerManager().ClearTimer(HealTimeHandle);
	
		if (IsDead())
		{
			OnDeathEvent.Broadcast();
		
		}
		else if (AutoHeal)
		{
			GetWorld()->GetTimerManager().SetTimer(HealTimeHandle,this, &UGGHealthComponent::HealUpdate,HealUpdateTime,true,HealDelay);
		}
}

void UGGHealthComponent::HealUpdate()
{
	SetHealth(Health + HealModifier);
	
	if( FMath::IsNearlyEqual(Health,MaxHealth) && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(HealTimeHandle);
	}
}

void UGGHealthComponent::SetHealth(float NewHealth)
{
		Health = FMath::Clamp(NewHealth, 0.0f , MaxHealth);
		OnHealthChangedEvent.Broadcast(Health);
		
		UE_LOG(LogHealthComponent,Display,TEXT("Health Broadcast %f"), Health)
}
void UGGHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME (UGGHealthComponent, Health);
}
