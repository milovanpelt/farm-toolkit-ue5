// Copyright Epic Games, Inc. All Rights Reserved.

#include "FarmEditor.h"
#include "FarmEditorStyle.h"
#include "FarmEditorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName FarmEditorTabName("FarmEditor");

#define LOCTEXT_NAMESPACE "FFarmEditorModule"

void FFarmEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FFarmEditorStyle::Initialize();
	FFarmEditorStyle::ReloadTextures();

	FFarmEditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FFarmEditorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FFarmEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FFarmEditorModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FarmEditorTabName, FOnSpawnTab::CreateRaw(this, &FFarmEditorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FFarmEditorTabTitle", "FarmEditor"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FFarmEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FFarmEditorStyle::Shutdown();

	FFarmEditorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FarmEditorTabName);
}

TSharedRef<SDockTab> FFarmEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FFarmEditorModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("FarmEditor.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FFarmEditorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(FarmEditorTabName);
}

void FFarmEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FFarmEditorCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FFarmEditorCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFarmEditorModule, FarmEditor)