// BSD 3-Clause License Copyright (c) 2022, Pierre Delaunay All rights reserved.

#pragma once

// Unreal Engine
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

// Generated
#include "ChessyPlayerController.generated.h"

UCLASS(Blueprintable)
class AChessyPlayerController: public APlayerController
{
    GENERATED_BODY()

    public:
    AChessyPlayerController();

    protected:
    /** True if the controlled character should navigate to the mouse cursor. */
    uint32 bMoveToMouseCursor : 1;

    // Begin PlayerController interface
    virtual void PlayerTick(float DeltaTime) override;
    virtual void SetupInputComponent() override;
    // End PlayerController interface

    /** Resets HMD orientation in VR. */
    void OnResetVR();

    /** Navigate player to the current mouse cursor location. */
    void MoveToMouseCursor();

    /** Navigate player to the current touch location. */
    void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);

    /** Navigate player to the given world location. */
    void SetNewMoveDestination(const FVector DestLocation);

    /** Input handlers for SetDestination action. */
    void OnSetDestinationPressed();
    void OnSetDestinationReleased();
};
