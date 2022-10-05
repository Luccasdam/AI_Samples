// Made by Luccas Machado. Feel free to use the code anyway you like!


#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LPatrolSystem.generated.h"

/*
 *	This still very simple. Changing the PatrolLocation to PatrolPoint (an TArray<"TSubclassOf" APatrolPoint>)
 *	This way the point can hold data, like next PatrolPoint, maybe a bit of randomness  NextPatrolSystem, WaitTime with Deviation, etc
 */
UCLASS()
class AI_SAMPLES_API ALPatrolSystem : public AActor
{
	GENERATED_BODY()

public:
	ALPatrolSystem();
	
	float GetPatrolToleranceDistance() const;
	
	FVector GetPatrolLocation(const uint8& PatrolIndex) const;
	
	uint8 GetClosestPatrolIndex(const FVector& ActorLocation) const;
	uint8 GetNextPatrolIndex(const uint8& PatrolIndex, bool& bReverse);

protected:
	UPROPERTY(VisibleAnywhere, Category=Components)
	UBillboardComponent* BillboardComp;

private:
	/** Should we loop or reverse when reach at last PatrolPoint */
	UPROPERTY(EditInstanceOnly, Category=Gameplay)
	bool bLoop;

	/** Distance to define that the Pawn is outside the system */
	UPROPERTY(EditInstanceOnly, Category=Gameplay)
	float PatrolToleranceDistance;

	/** PatrolPoints in the patrol order */
	UPROPERTY(EditInstanceOnly, Category=Gameplay, meta=(MakeEditWidget))
	TArray<FVector> PatrolLocations;
};
