// Gangland

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"

#include "GGHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GANGLAND_API UGGHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	//	VARIABLES BEGIN
	//=================//
public:

	//DELEGATES
	FOnDeathSignature OnDeathEvent;
	FOnHealthChangedSignature OnHealthChangedEvent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
	bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealUpdateTime = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealDelay = 3.0f;

	//How many points to heal
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "AutoHeal"))
	float HealModifier = 5.0f;

private:

	UPROPERTY(Replicated)
	float Health = 0.0f;
	
	FTimerHandle HealTimeHandle;
	
	//=================//
	//	VARIABLES END
	
	//	FUNCTIONS BEGIN
	//=================//
	
public:
	// Sets default values for this component's properties
	UGGHealthComponent();

	/** Property replication */
	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FORCEINLINE float GetHealth() const
	{
		return Health;
	}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsDead() const
	{
		return FMath::IsNearlyZero(Health);
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnTakeDamage
	(
		AActor* DamagedActor,
		float Damage,
		const class UDamageType* DamageType,
		class AController* InstigatedBy,
		AActor* DamageCauser
		);

	void HealUpdate();

	void SetHealth(float NewHealth);
	
	//=================//
	//	FUNCTIONS END
};
