// Made by Luccas Machado. Feel free to use the code anyway you like!


#include "AI/Components/LPatrolComponent.h"
#include "Common/LPatrolSystem.h"


ULPatrolComponent* ULPatrolComponent::GetPatrolComp(const APawn* TargetPawn)
{	return Cast<ULPatrolComponent>(TargetPawn->GetComponentByClass(ULPatrolComponent::StaticClass())); }

ULPatrolComponent::ULPatrolComponent()
	: bReverse(false)
	, CurrentPatrolIndex(UINT8_MAX)
{
}

bool ULPatrolComponent::HasPatrolSystem() const	{return IsValid(PatrolSystem);}

float ULPatrolComponent::GetPatrolToleranceDistance() const	{return PatrolSystem->GetPatrolToleranceDistance();}

FVector ULPatrolComponent::GetPatrolLocation()
{
	CurrentPatrolIndex = CurrentPatrolIndex == UINT8_MAX ?
		PatrolSystem->GetClosestPatrolIndex(GetOwner()->GetActorLocation()) :
		PatrolSystem->GetNextPatrolIndex(CurrentPatrolIndex, bReverse);

	return PatrolSystem->GetPatrolLocation(CurrentPatrolIndex);
}

