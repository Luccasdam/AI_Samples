// Made by Luccas Machado. Feel free to use the code anyway you like!


#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "LBTDecorator_IsTargetClose.generated.h"

/*
 *	Maybe make it use the Character Data to define this value by default
 *	In that case it would be helpful to have a "bForce" to use manual value
 */
UCLASS()
class AI_SAMPLES_API ULBTDecorator_IsTargetClose : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

	
public:
	ULBTDecorator_IsTargetClose();

private:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
	/** distance defined as close */
	UPROPERTY(EditAnywhere, Category=Condition, meta = (ClampMin = "0.0"))
	float CloseDistance;
};
