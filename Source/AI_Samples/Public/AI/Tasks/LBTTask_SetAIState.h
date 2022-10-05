// Made by Luccas Machado. Feel free to use the code anyway you like!


#pragma once
#include "CoreMinimal.h"
#include "AI/LAICharacter.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "LBTTask_SetAIState.generated.h"

/**
 *	// REVISE: This class is temporary for simplicity. When the project progress into using GAS or a simple version of it
 *	// we should make the use of GameplayTags to keep track of the AI State, extend the BehaviorTree and delete this BTTask
 */
UCLASS()
class AI_SAMPLES_API ULBTTask_SetAIState : public UBTTaskNode
{
	GENERATED_BODY()

public:
	ULBTTask_SetAIState();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere, Category=AI)
	EAIState NewAIState;

	UPROPERTY(EditAnywhere, Category=AI)
	bool bLockNode;
};
