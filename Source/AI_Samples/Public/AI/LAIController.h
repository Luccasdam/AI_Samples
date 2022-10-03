// Made by Luccas Machado. Feel free to use the code anyway you like!


#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "LAIController.generated.h"


UCLASS(Abstract)
class AI_SAMPLES_API ALAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* BT;
};
