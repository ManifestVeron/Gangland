// Gangland


#include "Player/GanglandBaseCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
AGanglandBaseCharacter::AGanglandBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AGanglandBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGanglandBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGanglandBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

