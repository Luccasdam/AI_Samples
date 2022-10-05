// Made by Luccas Machado. Feel free to use the code anyway you like!


#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "LBTDecorator_CanPatrol.generated.h"

/*
 *	Maybe CanPatrol requirement should be only if the AI has the PatrolComponent
 *	That way CanPatrol does not imply WantsPatrol Increasing Modularity.
 */
UCLASS()
class AI_SAMPLES_API ULBTDecorator_CanPatrol : public UBTDecorator
{
	GENERATED_BODY()

	
public:
	ULBTDecorator_CanPatrol();

private:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
