// Made by Luccas Machado. Feel free to use the code anyway you like!


#include "AI/Decorators/LBTDecorator_CanPatrol.h"
#include "AIController.h"
#include "AI/Components/LPatrolComponent.h"


ULBTDecorator_CanPatrol::ULBTDecorator_CanPatrol()
{
	NodeName = "Can Patrol";
}

bool ULBTDecorator_CanPatrol::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (const APawn* MyPawn = OwnerComp.GetAIOwner()->GetPawn())
	{
		if (const ULPatrolComponent* PatrolComp = ULPatrolComponent::GetPatrolComp(MyPawn))
			return PatrolComp->HasPatrolSystem();
	}	

	return false;
}
