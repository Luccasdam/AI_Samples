// Made by Luccas Machado. Feel free to use the code anyway you like!


#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LAICharacter.generated.h"


class UBehaviorTree;

UENUM(BlueprintType)
enum class EAIState : uint8
{
	EAIState_Idle,
	EAIState_Guard,
	EAIState_Suspicious,
	EAState_Investigating,
	EAIState_Alert,
	EAIState_Chasing,
	EAIState_Attacking
};


// REVISE: Should implement a singleton to hold static data?
USTRUCT(BlueprintType)
struct FAIAlertStateData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	uint8 AlertIconMinSize = 0;
	
	UPROPERTY(BlueprintReadOnly)
	uint8 AlertIconMaxSize = 100;

	UPROPERTY(BlueprintReadOnly)
	float AlertIconCooldown = 3.0f;
	
	UPROPERTY(BlueprintReadOnly)
	float AlertAnimationTime = 0.2f;

	UPROPERTY(BlueprintReadOnly)
	float AlertDurationTime = 0.5f;
};


// REVISE: Make it Multicast?
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateChanged, const EAIState&, NewAIState);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnStateChanged, const EAIState&, NewAIState);

UCLASS(Abstract)
class AI_SAMPLES_API ALAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALAICharacter();
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	// REVISE: Probably a bad practice using this const return. Just making this way o remember myself to take a look at it and study about this subject.
	const EAIState& GetAIState() const;

	UFUNCTION(BlueprintNativeEvent)
	void SetAIState(const EAIState& NewState);

	UBehaviorTree* GetBT() const;

protected:
	UFUNCTION()
	void OnKilled();

public:
	UPROPERTY()
	FOnStateChanged OnStateChanged;
	
protected:
	UPROPERTY(VisibleAnywhere, Category=Components)
	class ULAttributesComponent* AttributesComp;
	
	UPROPERTY(VisibleAnywhere, Category=Components)
	class ULPatrolComponent* PatrolComp;

	UPROPERTY(EditDefaultsOnly, Category=Components)
	TSubclassOf<class ALWeapon> WeaponClass;

	/** This will override AIController's BT */
	UPROPERTY(EditDefaultsOnly, Category=AI)
	UBehaviorTree* BT;
	
	UPROPERTY(BlueprintReadOnly, Category=AI)
	EAIState AIState;

	UPROPERTY(BlueprintReadWrite, Category=AI)
	bool bAlertIconOnCooldown = false;

private:
	UPROPERTY()
	ALWeapon* Weapon;
};
