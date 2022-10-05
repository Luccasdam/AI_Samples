// Made by Luccas Machado. Feel free to use the code anyway you like!


#include "AI/LAIController.h"

#include "AI/LAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"


ALAIController::ALAIController()
{
	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComp");
}

void ALAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AIPerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ALAIController::OnTargetPerceptionUpdated);
}


void ALAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	const ALAICharacter* LAICharacter = Cast<ALAICharacter>(GetPawn());
	ensure(LAICharacter);

	// This will only work for Single-Player
	if (Actor->GetNetOwningPlayer())
	{
		if (LAICharacter->GetAIState() == EAIState::EAIState_Idle)
			CachedPlayerRef = Stimulus.WasSuccessfullySensed() ? Actor : nullptr;
		else if (Stimulus.WasSuccessfullySensed())
			Blackboard->SetValueAsObject("TargetActor", Actor);
		else
			Blackboard->SetValueAsObject("TargetActor", nullptr);
	}	
}

// Maybe add a Sight_Config (& others Senses)  into the AICharacter and load into the PerceptionComp here
void ALAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	ALAICharacter* LAIC = Cast<ALAICharacter>(InPawn);
	if (LAIC != nullptr)
	{
		if (LAIC->GetBT())
			BT = LAIC->GetBT();

		LAIC->OnStateChanged.BindUFunction(this, "OnCharacterStateChanged");
	}

	RunBehaviorTree(BT);

	// TODO: Not the ideal way of adding values into Blackboard. It's Hard to keep track of the KeyName and could have problem with scalability. At least make a FName variable.
	Blackboard->SetValueAsVector("SpawnLocation", GetPawn()->GetActorLocation());
}

void ALAIController::OnCharacterStateChanged(const EAIState& NewState)
{
	if (NewState == EAIState::EAIState_Guard && IsValid(CachedPlayerRef) && LineOfSightTo(CachedPlayerRef))
		Blackboard->SetValueAsObject("TargetActor", CachedPlayerRef);

	CachedPlayerRef = nullptr;
}
