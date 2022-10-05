// Made by Luccas Machado. Feel free to use the code anyway you like!


#include "AI/Tasks/LBTTaskNode_GetPatrolLocation.h"
#include "AIController.h"
#include "AI/Components/LPatrolComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ULBTTaskNode_GetPatrolLocation::ULBTTaskNode_GetPatrolLocation()
{
	NodeName = "Get Patrol Location";

	// only accept vector
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(ULBTTaskNode_GetPatrolLocation, BlackboardKey));
}

EBTNodeResult::Type ULBTTaskNode_GetPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const APawn* MyPawn = OwnerComp.GetAIOwner()->GetPawn())
		if (ULPatrolComponent* PatrolComp = ULPatrolComponent::GetPatrolComp(MyPawn))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, PatrolComp->GetPatrolLocation());
			return EBTNodeResult::Succeeded;
		}

	return EBTNodeResult::Failed;
}
