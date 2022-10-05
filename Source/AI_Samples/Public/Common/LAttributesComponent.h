// Made by Luccas Machado. Feel free to use the code anyway you like!


#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LAttributesComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKilled);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AI_SAMPLES_API ULAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULAttributesComponent();
	
	static ULAttributesComponent* GetAttributesComponent(const AActor* TargetActor);

	// REVISE: If needed: Remove it from static and make a GameplayInterface that invoke this method.
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static void ApplyDamage(const AActor* DamagedActor, const float Damage);

	void SetInvulnerability(bool InvulnerableState);

	UPROPERTY()
	FOnKilled OnKilled;

private:	
	float MaxHealth;
	float Health;
	float bInvulnerable;
};
