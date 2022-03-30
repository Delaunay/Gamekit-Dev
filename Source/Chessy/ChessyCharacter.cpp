// BSD 3-Clause License Copyright (c) 2022, Pierre Delaunay All rights reserved.

#include "ChessyCharacter.h"
#include "Gamekit/Grid/GKHexGridUtilities.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/DecalComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "UObject/ConstructorHelpers.h"

FVector2D &GridSize()
{
    static FVector2D size;
    return size;
}

// Decal Component does not work
// The scale is wrong for some reason
/*
UDecalComponent* initializeCursorToWorld(AChessyCharacter* self){
        // Create a decal in the world to show the cursor's location
        UDecalComponent* CursorToWorld = self->CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
        CursorToWorld->SetupAttachment(self->GetRootComponent());
        // static ConstructorHelpers::FObjectFinder<UMaterial>
DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));

        static ConstructorHelpers::FObjectFinder<UMaterial>
DecalMaterialAsset(TEXT("Material'/Game/Tile/CursorDecal.CursorDecal'"));

        if (DecalMaterialAsset.Succeeded()) {
                CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
        }

        static ConstructorHelpers::FObjectFinder<UStaticMesh>
                        CursorMeshAsset(TEXT("StaticMesh'/Game/Tile/HexMesh.HexMesh'"));

        CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
        if (CursorMeshAsset.Succeeded()){
                UStaticMesh* obj = CursorMeshAsset.Object;
                auto size = obj->GetBoundingBox().GetSize();
                CursorToWorld->DecalSize = FVector(size.Z, size.X, size.Y);
                GridSize = UGKHexGridUtilities::GetHexSize(size);
        }

        CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());
        return CursorToWorld;
}
*/

AChessyCharacter::AChessyCharacter()
{
    // Set size for player capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

    // Don't rotate character to camera direction
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw   = false;
    bUseControllerRotationRoll  = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
    GetCharacterMovement()->RotationRate              = FRotator(0.f, 640.f, 0.f);
    GetCharacterMovement()->bConstrainToPlane         = true;
    GetCharacterMovement()->bSnapToPlaneAtStart       = true;

    // Create a camera boom...
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
    CameraBoom->TargetArmLength = 800.f;
    CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
    CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

    // Create a camera...
    TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
    TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

    // ---
    MeshCursor = CreateDefaultSubobject<UStaticMeshComponent>("MeshCursor");
    MeshCursor->SetupAttachment(GetRootComponent());
    MeshCursor->SetCastShadow(false);
    MeshCursor->SetCollisionResponseToAllChannels(ECR_Ignore);
    MeshCursor->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CursorMeshAsset(
            TEXT("StaticMesh'/Game/Tile/HexMesh.HexMesh'"));

    if (CursorMeshAsset.Succeeded())
    {
        MeshCursor->SetStaticMesh(CursorMeshAsset.Object);
        GridSize() = UGKHexGridUtilities::GetHexSize(CursorMeshAsset.Object->GetBoundingBox().GetSize());
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> CusorMaterialAsset(
            TEXT("Material'/Gamekit/Tiles/CursorMat.CursorMat'"));
    //	 CusorMaterialAsset(TEXT("Material'/Game/Tile/defaultMat.defaultMat'"));

    if (CusorMaterialAsset.Succeeded())
    {
        MeshCursor->SetMaterial(0, CusorMaterialAsset.Object);
    }
    // ---

    // Activate ticking in order to update the cursor every frame.
    PrimaryActorTick.bCanEverTick          = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
}

void AChessyCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (GetCursorToWorld() != nullptr)
    {
        if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
        {
            if (UWorld *World = GetWorld())
            {
                FHitResult            HitResult;
                FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
                FVector               StartLocation = TopDownCameraComponent->GetComponentLocation();
                FVector               EndLocation   = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
                Params.AddIgnoredActor(this);
                World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
                FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
                GetCursorToWorld()->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
            }
        }
        else if (APlayerController *PC = Cast<APlayerController>(GetController()))
        {
            FHitResult TraceHitResult;
            PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
            // FVector CursorFV = TraceHitResult.ImpactNormal;
            // FRotator CursorR = CursorFV.Rotation();
            // GetCursorToWorld()->SetWorldRotation(CursorR);

            auto CursorPosition =
                    UGKHexGridUtilities::SnapToGrid(GridSize(), TraceHitResult.Location - FVector(0, 0, 1));
            GetCursorToWorld()->SetWorldLocation(CursorPosition + FVector(0, 0, 0.01));
        }
    }
}
