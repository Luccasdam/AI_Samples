// Made by Luccas Machado. Feel free to use the code anyway you like!


#include "AI/LAICharacter.h"
#include "AI/Components/LPatrolComponent.h"
#include "Common/LAttributesComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon/LWeapon.h"


ALAICharacter::ALAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AttributesComp = CreateDefaultSubobject<ULAttributesComponent>("AttributesComp");
	PatrolComp = CreateDefaultSubobject<ULPatrolComponent>("PatrolComp");

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 270.f, 0.0f);
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void ALAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributesComp->OnKilled.AddDynamic(this, &ALAICharacter::OnKilled);
}

void ALAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (WeaponClass)
	{
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.Owner = this;
		Weapon = GetWorld()->SpawnActor<ALWeapon>(WeaponClass, ActorSpawnParams);
	}
}

const EAIState& ALAICharacter::GetAIState() const	{return AIState;}

void ALAICharacter::SetAIState_Implementation(const EAIState& NewState)
{
	AIState = NewState;
	OnStateChanged.Execute(AIState);
}

UBehaviorTree* ALAICharacter::GetBT() const	{return BT;}


void ALAICharacter::OnKilled()
{
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName("Ragdoll");

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();

	Weapon->SetLifeSpan(30.0f);
	SetLifeSpan(30.0f);
}
