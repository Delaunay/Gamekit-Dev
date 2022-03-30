// BSD 3-Clause License Copyright (c) 2022, Pierre Delaunay All rights reserved.

#include "GeneratedTestComponent.h"

// Sets default values for this component's properties
UGeneratedTestComponent::UGeneratedTestComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these
    // features off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Called when the game starts
void UGeneratedTestComponent::BeginPlay()
{
    Super::BeginPlay();

    // ...
}

// Called every frame
void UGeneratedTestComponent::TickComponent(float                        DeltaTime,
                                            ELevelTick                   TickType,
                                            FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}
