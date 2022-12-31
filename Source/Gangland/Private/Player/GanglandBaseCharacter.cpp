// Gangland

#include "Player/GanglandBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AGanglandBaseCharacter::AGanglandBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
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
	// Change control to Enhanted Player Inpute and Enhanted Pleyer Component
	PlayerInputComponent->BindAxis("MoveForward", this, &AGanglandBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGanglandBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AGanglandBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &AGanglandBaseCharacter::AddControllerYawInput);
}
// Change Enhanted Inpute Forward
void AGanglandBaseCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}
// Change Enhanted Inpute Forward
void AGanglandBaseCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}
