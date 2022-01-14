// BSD 3-Clause License Copyright (c) 2021, Pierre Delaunay All rights reserved.

#include "ChessyGameMode.h"
#include "ChessyPlayerController.h"
#include "ChessyCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "GameFramework/HUD.h"


AChessyGameMode::AChessyGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AChessyPlayerController::StaticClass();

	// static ConstructorHelpers::FClassFinder<AHUD> HUDClassBP(TEXT("/Game/HUD/HUD"));
	// if (HUDClassBP.Class != nullptr){
	// 	HUDClass = HUDClassBP.Class;
	// }

	// set default pawn class to our Blueprinted character
	// Blueprint'/Game/TopDownCPP/Blueprints/TopDownCharacter_Child.TopDownCharacter_Child'
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Mannequin/TopDownCharacter_Child"));
	// if (PlayerPawnBPClass.Class != nullptr){
	// 	DefaultPawnClass = PlayerPawnBPClass.Class;
	// }
}
