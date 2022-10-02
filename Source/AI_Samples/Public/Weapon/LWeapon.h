// Made by Luccas Machado. Feel free to use the code anyway you like!


#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LWeapon.generated.h"


USTRUCT()
struct FWeaponData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	bool bInfiniteAmmo;
	
	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	int32 MaxAmmo;
	
	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	int32 ClipSize;
	
	/** Fire rate in seconds till next fire */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float FireRate;

	/** Weapon spread amount in degrees */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float SpreadAmount;

	/** Weapon fire range */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Range;

	// Better to make a Bullet/Projectile Class that hold the Damage Data
	/** Weapon damage */
	float Damage;

	/** defaults */
	FWeaponData()
	{
		bInfiniteAmmo = true;
		MaxAmmo = 120;
		ClipSize = 30;
		FireRate = 0.2f;
		SpreadAmount = 3.0f;
		Range = 2500.f;
		Damage = 20.f;
	}
};
	

UCLASS(Abstract)
class AI_SAMPLES_API ALWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ALWeapon();

	virtual void BeginPlay() override;

	virtual void StartFire();
	virtual void StopFire();

	void FireWeapon() const;
	FVector GetAimDirection() const;
	FHitResult WeaponTrace(const FVector& TraceStart, const FVector& TraceEnd) const;	

	void AttachWeaponMeshToOwner() const;

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FWeaponData WeaponData;

	FTimerHandle TimerHandle_FireWeapon;
	
	UPROPERTY()
	int32 CurrentTotalAmmo;
	
	UPROPERTY()
	int32 CurrentClipAmmo;
	
	UPROPERTY(VisibleAnywhere, Transient, Category = "Components")
	UAudioComponent* FireAudioComp;

	UPROPERTY(VisibleAnywhere, Category = "SoundFX")
	USoundBase* ImpactSound;

	/** Usually would name it Mesh, but used "SK_" to "Mark" so I can change it later when I properly implement FirstPerson and ThirdPerson */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USkeletalMeshComponent* SK_Weapon;
};
