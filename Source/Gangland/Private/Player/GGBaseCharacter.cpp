// Gangland

#include "Player/GGBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/GGCharacterMovementComponent.h"
#include "Components/GGHealthComponent.h"
#include "Components/InputComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/GGWeaponComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"

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
	SpringArmComponent->SocketOffset = FVector(0.0f,100.0f, 200.0f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<UGGHealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
	HealthTextComponent->SetOwnerNoSee(true);

	WeaponComponent = CreateDefaultSubobject<UGGWeaponComponent>("WeaponComponent");
	
}

// Called when the game starts or when spawned
void AGGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);
	check(GetCharacterMovement());
	
	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeathEvent.AddUObject(this, &AGGBaseCharacter::OnDeath);
	HealthComponent->OnHealthChangedEvent.AddUObject(this, &AGGBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &AGGBaseCharacter::OnGroundeLanded);
}

// Called every frame
void AGGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Temp Health Remove after
	HealthTextComponent->SetText(Text);
}

// Called to bind functionality to input
void AGGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	check(PlayerInputComponent);
	check(WeaponComponent);
	
	// !!Change control to Enhanted Player Inpute and Enhanted Pleyer Component!! //
	PlayerInputComponent->BindAxis	("MoveForward",this, &AGGBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis	("MoveRight",this, &AGGBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis	("LookUp",this, &AGGBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis	("TurnAround",this, &AGGBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this, &AGGBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run",IE_Pressed,this, &AGGBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run",IE_Released,this, &AGGBaseCharacter::OnStopRunning);
	PlayerInputComponent->BindAction("Somersault",IE_Pressed,this,	&AGGBaseCharacter::OnStartSomersault);
	PlayerInputComponent->BindAction("Fire",IE_Pressed,WeaponComponent, &UGGWeaponComponent::Fire);
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
	bWantsToRun = true;
	IsRunning(bWantsToRun);
}

void AGGBaseCharacter::OnStopRunning()
{
	bWantsToRun = false;
	IsRunning(bWantsToRun);
}

void AGGBaseCharacter::IsRunning(bool running)
{
	bWantsToRun =  running && IsMovingForward && !GetVelocity().IsZero();
	if(!GetOwner()->HasAuthority())
	{
		ServerIsRunning(bWantsToRun);
	}
}

void AGGBaseCharacter::ServerIsRunning_Implementation(bool running)
{
	bWantsToRun = running;
}

bool AGGBaseCharacter:: Get_Running_for_Animation() const
{
	return bWantsToRun;
}

void AGGBaseCharacter::OnStartSomersault()
{
	bSomersault = true;
	IsSomersault(bSomersault);
	FTimerHandle Set_False_Somersault;
	GetWorld()->GetTimerManager().SetTimer(Set_False_Somersault,
		this,
		&AGGBaseCharacter::OnStopSomersault,
		1.0f,false,2.54f);
}

void AGGBaseCharacter::OnStopSomersault()
{
	bSomersault = false;
	IsSomersault(bSomersault);
}

void AGGBaseCharacter::IsSomersault(bool somersault)
{
	bSomersault =  somersault;
	if(!GetOwner()->HasAuthority())
	{
		ServerIsSomersault(bSomersault);
	}
}

void AGGBaseCharacter::ServerIsSomersault_Implementation(bool somersault)
{
	bSomersault = somersault;
}

bool AGGBaseCharacter:: Get_Somersault_for_Animation() const
{
	return bSomersault;
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
UGGHealthComponent* AGGBaseCharacter::GetHealthComponent() const
{
	return HealthComponent;
}
void AGGBaseCharacter::OnDeath()
{
		bIsDead = true;
		
		GetCharacterMovement()->DisableMovement();

		/* Вынести в Tools потом. Возможно ли вызывать это в Player Contoller через делегат? 
		auto const PC = Cast<AGGPlayerController>(GetOwner());
		if(PC) PC->GetSpectatorPawn()->SetActorLocationAndRotation(this->GetActorLocation(),this->GetActorRotation());
		*/
	
		SetLifeSpan(LifeSpanOnDeath);
		
}
//Death animations replications
void AGGBaseCharacter::PlayAnimationDeath()
{
	PlayAnimMontage(DeathAnimMontage);
}

//Temp Health
void AGGBaseCharacter::OnHealthChanged(float Health)
{
		Text = FText::FromString(FString::Printf(TEXT("%.0f"), Health));
		//HealthTextComponent->SetText(Text);
		/*GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.5f, FColor::Red, 
			Text.ToString());*/
}

void AGGBaseCharacter::OnGroundeLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetVelocity().Z;
	//UE_LOG(LogBaseCharacter, Display, TEXT("On landed %f"), FallVelocityZ);

	if(FallVelocityZ < LandedDamageVelocity.X)
	{
		return;
	}

	const auto FallDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	
	TakeDamage(FallDamage, FDamageEvent(), nullptr, nullptr);

	UE_LOG(LogBaseCharacter, Display, TEXT("Player %s recived landed damage %f"), *GetName(), FallDamage);
}

void AGGBaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME (AGGBaseCharacter, HealthTextComponent);
	DOREPLIFETIME (AGGBaseCharacter, Text);
	DOREPLIFETIME (AGGBaseCharacter, bIsDead);
	DOREPLIFETIME (AGGBaseCharacter, DeathAnimMontage);
	DOREPLIFETIME (AGGBaseCharacter, bWantsToRun);
	DOREPLIFETIME (AGGBaseCharacter, bSomersault);
}

  