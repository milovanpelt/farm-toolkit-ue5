// Copyright Epic Games, Inc. All Rights Reserved.

#include "FarmEditorCommands.h"

#define LOCTEXT_NAMESPACE "FFarmEditorModule"

void FFarmEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "FarmEditor", "Bring up FarmEditor window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
