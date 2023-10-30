// Gangland

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Math/Vector2D.h"

#include "GGBaseCharacter.generated.h"

class AGGBaseWeapon;
class USpringArmComponent;
class UCameraComponent;
class UGGHealthComponent;
class UTextRenderComponent;

UCLASS()
class GANGLAND_API AGGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

	//	VARIABLES BEGIN
	//=================//
	
public:

	
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UGGHealthComponent* HealthComponent;

	// Temp Health ->
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	FText Text;
	// <-Temp Health
	//Replication variable
	UPROPERTY(ReplicatedUsing = PlayAnimationDeath)
	bool bIsDead;
	
	UPROPERTY(Replicated, EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float LifeSpanOnDeath = 5.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AGGBaseWeapon> WeaponClass;

private:
	
	bool WantsToRun = false;
	bool IsMovingForward = false;

	//=================//
	//	VARIABLES END
	
	//	FUNCTIONS BEGIN
	//=================//
	
public:
	
	// Sets default values for this character's properties
	AGGBaseCharacter(const FObjectInitializer& ObjInit);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	FORCEINLINE float GetMovementDirection() const;
	
	//replication function for Death animation with bIsDead
	UFUNCTION()
	void PlayAnimationDeath();

	UFUNCTION()
	FORCEINLINE UGGHealthComponent* GetHealthComponent() const;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// !!Change control to Enhanted Player Inpute and Enhanted Pleyer Component!! //
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	// Run

	void OnStartRunning();
	void OnStopRunning();
	
	// !!Change control to Enhanted Player Inpute and Enhanted Pleyer Component!! /

	UFUNCTION()
	void OnGroundeLanded(const FHitResult& Hit);

	void OnHealthChanged(float Health);
	
	// DELEGATES
	void OnDeath();

	void SpawnWeapon() const;
	//=================//
	//	FUNCTIONS END
};
