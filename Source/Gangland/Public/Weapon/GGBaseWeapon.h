// Gangland

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GGBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class GANGLAND_API AGGBaseWeapon : public AActor
{
	GENERATED_BODY()
	
	//	VARIABLES BEGIN
	//=================//
	
public:
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= "Components")
	USkeletalMeshComponent* WeaponMeshComponent;
	
private:
	
	//=================//
	//	VARIABLES END
	
	//	FUNCTIONS BEGIN
	//=================//
	
public:	
	// Sets default values for this actor's properties
	AGGBaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	
	//=================//
	//	FUNCTIONS END

};
