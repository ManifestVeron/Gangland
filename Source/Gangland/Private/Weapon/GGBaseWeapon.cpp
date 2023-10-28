// Gangland


#include "Weapon/GGBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AGGBaseWeapon::AGGBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon Mesh Component");
	SetRootComponent(WeaponMeshComponent);
}

// Called when the game starts or when spawned
void AGGBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}


