// Made by Luccas Machado. Feel free to use the code anyway you like!


#include "AI/Decorators/LBTDecorator_IsTargetClose.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "VisualLogger/VisualLogger.h"


ULBTDecorator_IsTargetClose::ULBTDecorator_IsTargetClose()
{
	NodeName = "Is Target Close";

	// accept only actors and vectors
	BlackboardKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ULBTDecorator_IsTargetClose, BlackboardKey), AActor::StaticClass());
	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(ULBTDecorator_IsTargetClose, BlackboardKey));
}

bool ULBTDecorator_IsTargetClose::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const AAIController* MyAIC = OwnerComp.GetAIOwner();
	const UBlackboardComponent* MyBB = OwnerComp.GetBlackboardComponent();
	FVector TargetLocation;

	// get TargetLocation. Probably better make another method to keep simplicity
	// should I log or just fail?
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		const UObject* KeyValue = MyBB->GetValueAsObject(BlackboardKey.SelectedKeyName);
		if (const AActor* TargetActor = Cast<AActor>(KeyValue))
			TargetLocation = TargetActor->GetActorLocation();
		else
			UE_VLOG(MyAIC, LogBehaviorTree, Warning, TEXT("ULBTDecorator_IsTargetClose::CalculateConditionValue tried to get TargetActor Location while BB %s entry was not valid"), *BlackboardKey.SelectedKeyName.ToString());
	}
	else if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
		TargetLocation = MyBB->GetValueAsVector(BlackboardKey.SelectedKeyName);
	else
		UE_VLOG(MyAIC, LogBehaviorTree, Warning, TEXT("ULBTDecorator_IsTargetClose::CalculateConditionValue tried to get TargetLocation while BB %s entry was empty"), *BlackboardKey.SelectedKeyName.ToString());

	
	// gets distance from AIPawn Location to TargetLocation
	if (const APawn* AIPawn = MyAIC->GetPawn())
		return FVector::Distance(AIPawn->GetActorLocation(), TargetLocation) <= CloseDistance;
	else
		UE_VLOG(MyAIC, LogBehaviorTree, Warning, TEXT("ULBTDecorator_IsTargetClose::CalculateConditionValue tried to get AIPawn Location while it is not valid"));
	return false;
}
