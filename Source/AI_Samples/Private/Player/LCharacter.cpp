// Made by Luccas Machado. Feel free to use the code anyway you like!


#include "Player/LCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Common/LAttributesComponent.h"
#include "Weapon/LWeapon.h"


ALCharacter::ALCharacter()
	: bWantsToFire(false)
	, bWantsToIronSight(false)
	, IronSightAlpha(0.0f)
	, IronSightSpeed(4.0f)
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	AttributesComp = CreateDefaultSubobject<ULAttributesComponent>("AttributesComp");
}

void ALCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	// TODO: Disable Invulnerability by default.
	AttributesComp->SetInvulnerability(true);
	AttributesComp->OnKilled.AddDynamic(this, &ALCharacter::OnKilled);
}

void ALCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponClass)
	{
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.Owner = this;
		Weapon = GetWorld()->SpawnActor<ALWeapon>(WeaponClass, ActorSpawnParams);
	}
}

void ALCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateIronSight(DeltaSeconds);
}


void ALCharacter::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	OutLocation = CameraComp->GetComponentLocation();
	OutRotation = GetControlRotation();
}


void ALCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ALCharacter::StartWeaponFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ALCharacter::StopWeaponFire);
	PlayerInputComponent->BindAction("AlternativeFire", IE_Pressed, this, &ALCharacter::StartIronSight);
	PlayerInputComponent->BindAction("AlternativeFire", IE_Released, this, &ALCharacter::StopIronSight);
}


void ALCharacter::MoveForward(float Value)
{
	if (Controller && Value)
	{
		const FVector Direction = FQuatRotationMatrix(GetActorQuat()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ALCharacter::MoveRight(float Value)
{
	if (Controller && Value)
	{
		const FVector Direction = FQuatRotationMatrix(GetActorQuat()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

// TODO: Probably Make a OnStart/OnStop WeaponFire with some validations for better control and avoid bugs.
// TODO: At the moment the weapon is always valid and fixed. When implement a better weapon system, check if the weapon is valid and which weapon is using
void ALCharacter::StartWeaponFire()	{Weapon->StartFire();}

void ALCharacter::StopWeaponFire()	{Weapon->StopFire();}

void ALCharacter::StartIronSight()	{bWantsToIronSight = true;}

void ALCharacter::StopIronSight()	{bWantsToIronSight = false;}

void ALCharacter::UpdateIronSight(float DeltaSeconds)
{
	if ((bWantsToIronSight && IronSightAlpha != 1.0f) || (!bWantsToIronSight && IronSightAlpha != 0.0f))
	{
		DeltaSeconds *= IronSightSpeed;
		IronSightAlpha += bWantsToIronSight ? DeltaSeconds : -DeltaSeconds;
		IronSightAlpha = FMath::Clamp(IronSightAlpha, 0.0f, 1.0f);
	
		CameraComp->FieldOfView = FMath::Lerp(90.f, 45.f, IronSightAlpha);
	}
}

void ALCharacter::OnKilled()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Killed"))
}