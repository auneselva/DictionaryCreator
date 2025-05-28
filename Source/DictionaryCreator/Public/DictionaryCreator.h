// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "Widgets/Docking/SDockTab.h"

class FDictionaryCreatorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	void RegisterMenu();
	TSharedRef<SDockTab> SpawnMainTab(const FSpawnTabArgs& Args);
	
};
