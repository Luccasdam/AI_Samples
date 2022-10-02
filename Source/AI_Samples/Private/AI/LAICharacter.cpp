// Made by Luccas Machado. Feel free to use the code anyway you like!


#include "AI/LAICharacter.h"
#include "Common/LAttributesComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapon/LWeapon.h"


ALAICharacter::ALAICharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	AttributesComp = CreateDefaultSubobject<ULAttributesComponent>("AttributesComp");
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


void ALAICharacter::OnKilled()
{
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetCollisionProfileName("Ragdoll");

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->DisableMovement();

	Weapon->SetLifeSpan(30.0f);
	SetLifeSpan(30.0f);
}
