// Copyright Epic Games, Inc. All Rights Reserved.

#include "CombatPortfolioGameMode.h"
#include "CombatPortfolioCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACombatPortfolioGameMode::ACombatPortfolioGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
