// Made by Luccas Machado. Feel free to use the code anyway you like!


#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "LAICharacter.h"
#include "Perception/AIPerceptionTypes.h"
#include "LAIController.generated.h"


UCLASS(Abstract)
class AI_SAMPLES_API ALAIController : public AAIController
{
	GENERATED_BODY()

public:
	ALAIController();
	virtual void PostInitializeComponents() override;

protected:	
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void OnCharacterStateChanged(const EAIState& NewState);

protected:
	UPROPERTY(EditDefaultsOnly, Category=AI)
	class UBehaviorTree* BT;
		
	UPROPERTY(EditDefaultsOnly, Category=Components)
	class UAIPerceptionComponent* AIPerceptionComp;

	UPROPERTY()
	AActor* CachedPlayerRef;
};
