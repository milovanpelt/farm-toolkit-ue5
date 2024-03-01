// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FFarmEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:
	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

	TSharedPtr<class FUICommandList> PluginCommands;

	FReply CreateCrop();

	FReply CreateSeed();

	FReply OpenCropWindow();

	FReply OpenSeedWindow();

	EVisibility GetCropWindowVisibility() const;

	EVisibility GetSeedWindowVisibility() const;
private:
	bool m_isCropWindowVisible = true;
	bool m_isSeedWindowVisible = false;

	// String data for seeds and crops
	TArray<TSharedPtr<FString>> SeedNames;
	TArray<TSharedPtr<FString>> CropNames;

	// Listview Widget
	TSharedPtr< SListView<TSharedPtr<FString>> > ListViewWidget;

	// Generate row for the ListView Widget
	TSharedRef<ITableRow> OnGenerateRowForList(TSharedPtr<FString> Item, const TSharedRef<STableViewBase>& OwnerTable);
};