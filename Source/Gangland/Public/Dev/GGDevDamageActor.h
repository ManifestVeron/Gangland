// Gangland

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGDevDamageActor.generated.h"

UCLASS()
class GANGLAND_API AGGDevDamageActor : public AActor
{
	GENERATED_BODY()

	//	VARIABLES BEGIN
	//=================//
	
public:	
	// Sets default values for this actor's properties
	AGGDevDamageActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor SphereColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DoFullDamage = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;
	
protected:
	
private:
	
	//=================//
	//	VARIABLES END
	
	//	FUNCTIONS BEGIN
	//=================//
	
public:
	
	virtual void Tick(float DeltaTime) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	
	//=================//
	//	FUNCTIONS END
};
