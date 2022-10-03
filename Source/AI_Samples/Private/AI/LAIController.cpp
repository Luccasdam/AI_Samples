// Made by Luccas Machado. Feel free to use the code anyway you like!


#include "AI/LAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


void ALAIController::BeginPlay()
{
	Super::BeginPlay();
	
	RunBehaviorTree(BT);

	// This is cheating and poorly implemented. Just for testing purpose
	Blackboard->SetValueAsObject("TargetActor", UGameplayStatics::GetPlayerCharacter(this, 0));
}
