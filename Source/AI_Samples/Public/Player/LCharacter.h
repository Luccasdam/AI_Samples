// Made by Luccas Machado. Feel free to use the code anyway you like!


#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LCharacter.generated.h"


UCLASS(Abstract)
class AI_SAMPLES_API ALCharacter : public ACharacter
{
	GENERATED_BODY()

	
public:
	ALCharacter();
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual bool HasWeapon() const;

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void StartWeaponFire();
	void StopWeaponFire();

	void StartIronSight();
	void StopIronSight();
	void UpdateIronSight(float DeltaSeconds);

	UFUNCTION()
	void OnKilled();

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, Category=Components)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category=Components)
	class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category=Components)
	class ULAttributesComponent* AttributesComp;

	UPROPERTY(EditDefaultsOnly, Category=Components)
	TSubclassOf<class ALWeapon> WeaponClass;

private:
	bool bWantsToFire;
	bool bWantsToIronSight;

	float IronSightAlpha;
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	float IronSightSpeed;

	UPROPERTY()
	ALWeapon* Weapon;
};
