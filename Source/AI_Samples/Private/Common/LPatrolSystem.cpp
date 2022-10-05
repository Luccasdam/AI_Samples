// Made by Luccas Machado. Feel free to use the code anyway you like!


#include "Common/LPatrolSystem.h"
#include "Components/BillboardComponent.h"

// TODO: THis class is making more than is supposed to. Transfer some responsibilities to the PatrolComponent.


ALPatrolSystem::ALPatrolSystem()
	: bLoop(false)
	, PatrolToleranceDistance(100.f)
{
	BillboardComp = CreateDefaultSubobject<UBillboardComponent>("BillboardComp");
	SetRootComponent(BillboardComp);
}

float ALPatrolSystem::GetPatrolToleranceDistance() const	{return PatrolToleranceDistance;}

FVector ALPatrolSystem::GetPatrolLocation(const uint8& PatrolIndex) const
{	
	return GetActorLocation() + PatrolLocations[PatrolIndex];
}


uint8 ALPatrolSystem::GetClosestPatrolIndex(const FVector& ActorLocation) const
{
	// REVISE: Not the best way but will do for now. If there's not at least 2 PatrolLocations we should not be Patrolling.
	if (ensure (PatrolLocations.IsValidIndex(0) && PatrolLocations.Num() > 2))
	{
		uint8 BestIndex = 0;
		float ClosestDistance = FVector::Distance(PatrolLocations[0], ActorLocation);

		for (uint8 i = 1; i < PatrolLocations.Num(); i++)
		{
			const float Distance = FVector::Distance(PatrolLocations[i], ActorLocation);
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				BestIndex = i;
			}
		}

		return BestIndex;
	}

	UE_LOG(LogTemp, Warning, TEXT("PatrolSystem: Trying to get ClosestPatrol but there should be at least 2 Locations"))
	return 0;
}

// REVISE: This should not Direct Set bReveset value. As a Get function, make is const.
// Can Verify, From PatrolComponent if the next PatrolIndex is valid (In another method of this class) and return a bool to control the Reverse
// That way not only make it easier to control & Debug but also increase the flexibility to do something at end points
// The Goal could be reach the end of the Patrol then do Something else
// Or maybe add a PathSystem that isn't the same as Patrol?
// Those Events/Decisions can be stored in the Patrol/Path Point as well (And even consumed!)
uint8 ALPatrolSystem::GetNextPatrolIndex(const uint8& PatrolIndex, bool& bReverse)
{
	// Check out of range
	if (PatrolIndex == 0 && bReverse || PatrolIndex == PatrolLocations.Num()-1 && !bReverse)
	{
		if (bLoop)
		{
			return bReverse ? PatrolLocations.Num()-1 : 0;
		}			
		
		bReverse = !bReverse;
	}
	
	return bReverse ? PatrolIndex-1 : PatrolIndex+1;
}
