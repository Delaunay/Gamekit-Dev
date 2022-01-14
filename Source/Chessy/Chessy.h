// BSD 3-Clause License Copyright (c) 2021, Pierre Delaunay All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogChessy, Log, All);


class FIChessyModule: public IModuleInterface {
public:
    virtual void StartupModule() override;

    virtual void ShutdownModule() override;
};
