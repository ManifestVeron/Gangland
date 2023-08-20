// Gangland

#include "Player/GGBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/GGCharacterMovementComponent.h"
#include "Components/GGHealthComponent.h"
#include "Components/InputComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

// Sets default values
AGGBaseCharacter::AGGBaseCharacter(const FObjectInitializer& ObjInit)
: Super(ObjInit.SetDefaultSubobjectClass<UGGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<UGGHealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AGGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &AGGBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AGGBaseCharacter::OnHealthChanged);
}

// Called every frame
void AGGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// !!Change control to Enhanted Player Inpute and Enhanted Pleyer Component!! //
	PlayerInputComponent->BindAxis("MoveForward", this, &AGGBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGGBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AGGBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnAround", this, &AGGBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AGGBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AGGBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AGGBaseCharacter::OnStopRunning);
}

void AGGBaseCharacter::MoveForward(float Amount)
{
	if (Amount == 0.0f)
		return;

	IsMovingForward = Amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AGGBaseCharacter::MoveRight(float Amount)
{
	if (Amount == 0.0f)
		return;

	AddMovementInput(GetActorRightVector(), Amount);
}

// Running//

void AGGBaseCharacter::OnStartRunning()
{
	WantsToRun = true;
}

void AGGBaseCharacter::OnStopRunning()
{
	WantsToRun = false;
}

bool AGGBaseCharacter::IsRunning() const
{
	return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

// !!Change control to Enhanted Player Inpute and Enhanted Pleyer Component!! //

float AGGBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero())
		return 0.0f;

	const auto VelocityNormal = GetVelocity().GetSafeNormal();

	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));

	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

	const auto Degress = FMath::RadiansToDegrees(AngleBetween);

	return CrossProduct.IsZero() ? Degress : Degress * FMath::Sign(CrossProduct.Z);
}

void AGGBaseCharacter::OnDeath()
{
	UE_LOG(LogBaseCharacter, Display, TEXT("Player %s is dead!"), *GetName());

	PlayAnimMontage(DeathAnimMontage);

	GetCharacterMovement()->DisableMovement();

	SetLifeSpan(5.0f);
	
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void AGGBaseCharacter::OnHealthChanged(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}