// Made by Luccas Machado. Feel free to use the code anyway you like!


#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LPatrolComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AI_SAMPLES_API ULPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	static ULPatrolComponent* GetPatrolComp(const APawn* TargetPawn);
	
	ULPatrolComponent();

	bool HasPatrolSystem() const;

	float GetPatrolToleranceDistance() const;
	FVector GetPatrolLocation();


protected:
	/** Should begin in reverse flow */
	UPROPERTY(EditInstanceOnly, Category=Gameplay)
	bool bReverse;
	
	// REVISE: Can make it as TArray to make it possible to move through other Patrol Systems. But for that probably use LocationActors instead Vectors inside Patrol System.
	UPROPERTY(EditInstanceOnly, Category=Gameplay)
	class ALPatrolSystem* PatrolSystem;

private:
	UPROPERTY()
	uint8 CurrentPatrolIndex;
};
