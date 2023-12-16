// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "FarmEditorStyle.h"

class FFarmEditorCommands : public TCommands<FFarmEditorCommands>
{
public:

	FFarmEditorCommands()
		: TCommands<FFarmEditorCommands>(TEXT("FarmEditor"), NSLOCTEXT("Contexts", "FarmEditor", "FarmEditor Plugin"), NAME_None, FFarmEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};