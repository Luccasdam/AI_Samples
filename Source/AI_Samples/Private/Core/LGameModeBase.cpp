// Made by Luccas Machado. Feel free to use the code anyway you like!


#include "Core/LGameModeBase.h"


ALGameModeBase::ALGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnObject(TEXT("/Game/Blueprints/Player/BP_PlayerCharacter"));
	DefaultPawnClass = PlayerPawnObject.Class;
}