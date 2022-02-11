// Copyright Epic Games, Inc. All Rights Reserved.

#include "SimpleIKGameMode.h"
#include "SimpleIKCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASimpleIKGameMode::ASimpleIKGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
