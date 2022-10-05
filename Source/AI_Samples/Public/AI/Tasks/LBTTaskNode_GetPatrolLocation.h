// Made by Luccas Machado. Feel free to use the code anyway you like!


#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "LBTTaskNode_GetPatrolLocation.generated.h"


UCLASS()
class AI_SAMPLES_API ULBTTaskNode_GetPatrolLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	ULBTTaskNode_GetPatrolLocation();
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere, Category=AI)
	FBlackboardKeySelector BlackboardKey;
};
