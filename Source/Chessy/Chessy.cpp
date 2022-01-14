// BSD 3-Clause License Copyright (c) 2021, Pierre Delaunay All rights reserved.

#include "Chessy.h"
#include "Modules/ModuleManager.h"

#include "Engine/Blueprint.h"


DEFINE_LOG_CATEGORY(LogChessy)

void FIChessyModule::StartupModule() {
	FString ShaderDirectory = FPaths::Combine(FPaths::ProjectDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping("/Project", ShaderDirectory);
}

void FIChessyModule::ShutdownModule() {
	ResetAllShaderSourceDirectoryMappings();
}

IMPLEMENT_PRIMARY_GAME_MODULE( FIChessyModule, Chessy, "Chessy" );
