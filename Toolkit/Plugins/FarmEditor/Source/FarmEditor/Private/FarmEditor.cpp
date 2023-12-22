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
	/*FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FFarmEditorModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("FarmEditor.cpp"))
		);*/

	return SNew(SDockTab)
	.TabRole(ETabRole::NomadTab)
	[
		SNew(SBorder)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				// Creating crops tab
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Left)
				.AutoWidth()
				[
					SNew(SButton)
					.Text(FText::FromString("Add Crops"))
					.OnClicked_Raw(this, &FFarmEditorModule::OpenCropWindow)
				]

				// Creating seeds tab
				+ SHorizontalBox::Slot()
				.Padding(FMargin(10, 0))
				.AutoWidth()
				[
					SNew(SButton)
					.Text(FText::FromString("Add Seeds"))
					.OnClicked_Raw(this, &FFarmEditorModule::OpenSeedWindow)
				]
			]
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				// Seed and Crop windows
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				[
					SNew(SOverlay)
					+ SOverlay::Slot()
					.VAlign(VAlign_Fill)
					[
						SNew(SBorder)
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.Padding(FMargin(50.0f))
						[
							SNew(SButton)
							.Text(LOCTEXT("CreateCropButton", "Create Crop"))
							.OnClicked_Raw(this, &FFarmEditorModule::CreateCrop)
						]
					]
					+ SOverlay::Slot()
					.VAlign(VAlign_Fill)
					[
						SNew(SBorder)
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Fill)
						.Padding(FMargin(50.0f))
						[
							SNew(SButton)
							.Text(LOCTEXT("CreateSeedButton", "Create Seed"))
							.OnClicked_Raw(this, &FFarmEditorModule::CreateSeed)
						]
					] // End of overlay slot
				] // End of horizontalbox slot
			
			] // End of verticalbox slot

		] // End of border slot
	];
}

FReply FFarmEditorModule::CreateCrop()
{
	UE_LOG(LogTemp, Warning, TEXT("Crop Created"));
	return FReply::Handled();
}

FReply FFarmEditorModule::CreateSeed()
{
	UE_LOG(LogTemp, Warning, TEXT("Seed Created"));
	return FReply::Handled();
}

FReply FFarmEditorModule::OpenCropWindow()
{
	
	return FReply::Handled();
}

FReply FFarmEditorModule::OpenSeedWindow()
{
	
	return FReply::Handled();
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