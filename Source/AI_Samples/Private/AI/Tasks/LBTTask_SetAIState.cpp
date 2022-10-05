// Made by Luccas Machado. Feel free to use the code anyway you like!


#include "AI/Tasks/LBTTask_SetAIState.h"
#include "AIController.h"
#include "AI/LAICharacter.h"


ULBTTask_SetAIState::ULBTTask_SetAIState()
{
	NodeName = "Set AIState ";
	bLockNode = false;
}

EBTNodeResult::Type ULBTTask_SetAIState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* MyAIC = OwnerComp.GetAIOwner();
	
	if (ALAICharacter* MyLAIC = Cast<ALAICharacter>(MyAIC->GetPawn()))
	{		
		MyLAIC->SetAIState(NewAIState);
		return bLockNode ? EBTNodeResult::InProgress : EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
