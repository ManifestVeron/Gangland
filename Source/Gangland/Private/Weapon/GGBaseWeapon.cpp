// Gangland


#include "Weapon/GGBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

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

void AGGBaseWeapon::Fire()
{
	UE_LOG(LogBaseWeapon, Display, TEXT("Fire!"));
}


