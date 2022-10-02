// Made by Luccas Machado. Feel free to use the code anyway you like!


#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LAICharacter.generated.h"


UCLASS()
class AI_SAMPLES_API ALAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALAICharacter();
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void OnKilled();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class ULAttributesComponent* AttributesComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TSubclassOf<class ALWeapon> WeaponClass;

private:
	UPROPERTY()
	ALWeapon* Weapon;
};
