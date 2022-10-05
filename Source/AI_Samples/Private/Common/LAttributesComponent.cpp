// Made by Luccas Machado. Feel free to use the code anyway you like!


#include "Common/LAttributesComponent.h"


ULAttributesComponent* ULAttributesComponent::GetAttributesComponent(const AActor* TargetActor)
{
	return Cast<ULAttributesComponent>(TargetActor->GetComponentByClass(ULAttributesComponent::StaticClass()));
}


ULAttributesComponent::ULAttributesComponent()
	: MaxHealth(100.0f)
	, Health(MaxHealth)
	, bInvulnerable(false)
{
	PrimaryComponentTick.bCanEverTick = false;
}


void ULAttributesComponent::ApplyDamage(const AActor* DamagedActor, const float Damage)
{
	if (!DamagedActor || !Damage)	return;

	if (ULAttributesComponent* Comp = GetAttributesComponent(DamagedActor))
	{
		if (Comp->bInvulnerable)	return;
		
		Comp->Health -= Damage;
		Comp->Health = FMath::Clamp(Comp->Health, 0.0f, Comp->MaxHealth);

		if (Comp->Health == 0.0f)
			Comp->OnKilled.Broadcast();

		UE_LOG(LogTemp, Warning, TEXT("%s: received %f Damage."), *GetNameSafe(DamagedActor), Damage)
	}	
}

void ULAttributesComponent::SetInvulnerability(bool InvulnerableState)	{bInvulnerable = InvulnerableState;}
