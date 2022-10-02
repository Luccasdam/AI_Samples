// Made by Luccas Machado. Feel free to use the code anyway you like!

#include "Weapon/LWeapon.h"
#include "DrawDebugHelpers.h"
#include "Common/LAttributesComponent.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/LCharacter.h"


ALWeapon::ALWeapon()
	: CurrentTotalAmmo(WeaponData.MaxAmmo)
	, CurrentClipAmmo(WeaponData.ClipSize)
{
	PrimaryActorTick.bCanEverTick = false;

	SK_Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon Mesh");
	SetRootComponent(SK_Weapon);

	FireAudioComp = CreateDefaultSubobject<UAudioComponent>("FireAudioComp");
	FireAudioComp->SetupAttachment(SK_Weapon, "MuzzleSocket");
	FireAudioComp->bAutoActivate = false;
}

void ALWeapon::BeginPlay()
{
	Super::BeginPlay();
	AttachWeaponMeshToOwner();
}

void ALWeapon::StartFire()
{
	if (GetOwner() && CurrentClipAmmo)
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_FireWeapon, this, &ALWeapon::FireWeapon, WeaponData.FireRate, true);
}

void ALWeapon::StopFire()	{GetWorld()->GetTimerManager().ClearTimer(TimerHandle_FireWeapon);}


// Better divide the function into smaller methods
// TODO: There is no track of Ammo. Should implement this after the initial gameplay implementation.
void ALWeapon::FireWeapon() const
{
	FireAudioComp->Play();
	
	const int32 RandSeed = FMath::Rand();
	const FRandomStream RandStream(RandSeed);
	const float ConeHalfAngleRad = FMath::DegreesToRadians(WeaponData.SpreadAmount * 0.5f);

	// Would be better to make a FName variable to Store the SocketLocationName
	const FVector TraceStart = SK_Weapon->GetSocketLocation("MuzzleSocket");
	const FVector AimDirection = GetAimDirection();
	const FVector ShootDirection = RandStream.VRandCone(AimDirection, ConeHalfAngleRad, ConeHalfAngleRad);
	const FVector TraceEnd = TraceStart + ShootDirection * WeaponData.Range;

	const FHitResult Hit = WeaponTrace(TraceStart, TraceEnd);
	if (Hit.bBlockingHit)
	{
		ULAttributesComponent::ApplyDamage(Hit.GetActor(), WeaponData.Damage);

		if (ImpactSound)
			UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, Hit.ImpactPoint);
	}		
}

FVector ALWeapon::GetAimDirection() const
{
	/** Lets ensure that there is a Owner responsible for shooting the weapon, otherwise something is probably wrong */
	if (!ensure(GetOwner()))	return FVector::ZeroVector;
		
	/** Lets ensure that the Owner has a Controller */
	const AController* Controller = GetOwner()->GetInstigatorController();
	if (ensure(Controller))
	{
		if (Controller->IsPlayerController())
		{
			// This is overridden to get the CameraViewPoint
			FVector EyeLocation;
			FRotator EyeRotation;
			GetOwner()->GetActorEyesViewPoint(EyeLocation, EyeRotation);

			const FVector TraceEnd = EyeLocation + EyeRotation.Vector() * WeaponData.Range;
			const FHitResult Hit = WeaponTrace(EyeLocation, TraceEnd);

			const FVector StartLocation = SK_Weapon->GetSocketLocation("MuzzleSocket");
			const FVector TargetLocation = Hit.bBlockingHit ? Hit.ImpactPoint : Hit.TraceEnd;

			return (TargetLocation - StartLocation).GetSafeNormal(1.0f);
		}
		else
			return Controller->GetControlRotation().Vector();
	}

	UE_LOG(LogTemp, Warning, TEXT("Weapon could not find Aim Direction"))
	return FVector::ZeroVector;
}

FHitResult ALWeapon::WeaponTrace(const FVector& TraceStart, const FVector& TraceEnd) const
{
	// TODO: If Weapon trace is not good make a CollisionQueryParams
	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility);

	// TODO: Make a ConsoleVariableCommand for quick and easy debugging
	// Uncomment this for debug.
	// const FColor HitColor = Hit.bBlockingHit ? FColor::Red : FColor::Green;
	// DrawDebugLine(GetWorld(), TraceStart, TraceEnd, HitColor, false,  0.2f, 0, 2.0f);

	return Hit;
}

void ALWeapon::AttachWeaponMeshToOwner() const
{
	/** If there's no Owner, we shouldn't try to attach */
	if (ensure(GetOwner()))
	{
		/** For now The Owner Must be a Character */
		const ACharacter* OwningCharacter = Cast<ACharacter>(GetOwner());
		if (!OwningCharacter)	return;

		SK_Weapon->AttachToComponent(OwningCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "WeaponSocket");
	}
}