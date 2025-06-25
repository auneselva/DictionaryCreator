// by Agnieszka Konopka, May 2025.

#include "DictionaryCreator.h"
#include "SDictionaryCreatorMainWindow.h"

#define LOCTEXT_NAMESPACE "FDictionaryCreatorModule"

static const FName DictionaryCreatorTabName("DictionaryCreator");

void FDictionaryCreatorModule::StartupModule()
{
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(
		DictionaryCreatorTabName,
		FOnSpawnTab::CreateRaw(this, &FDictionaryCreatorModule::SpawnMainTab))
		.SetDisplayName(LOCTEXT("DictionaryCreator", "Dictionary Creator"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
	RegisterMenu();
}

void FDictionaryCreatorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(DictionaryCreatorTabName);
}

void FDictionaryCreatorModule::RegisterMenu()
{
	FToolMenuOwnerScoped OwnerScoped(this);
	UToolMenu* Menu = UToolMenus::Get()->FindMenu("LevelEditor.MainMenu.Plugins");
	if (!Menu)
	{
		Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu");
		FToolMenuSection& Section = Menu->FindOrAddSection("Plugins");
		FToolMenuEntry& Entry = Section.AddSubMenu(
			"Plugins",
			LOCTEXT("AddMenu_Plugins", "Plugins"),
			LOCTEXT("AddMenu_PluginsToolTip", "Plugins"),
			FNewToolMenuChoice()
			);
		Entry.InsertPosition = FToolMenuInsert("Help", EToolMenuInsertType::After);
		Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Plugins");
	}
	
	FToolMenuSection& SectionMenu = Menu->FindOrAddSection("FileTools", FText::FromString("File Tools"));
		SectionMenu.AddMenuEntry(
			DictionaryCreatorTabName,
			LOCTEXT("AddMenu_DictionaryCreator", "Dictionary Creator"),
			FText::FromString("Dictionary Creator"),
			FSlateIcon(),
			FExecuteAction::CreateLambda([]()
			{
				FGlobalTabmanager::Get()->TryInvokeTab(DictionaryCreatorTabName);
			}));
}

TSharedRef<SDockTab> FDictionaryCreatorModule::SpawnMainTab(const FSpawnTabArgs& Args)
{
	return SNew(SDockTab).TabRole(NomadTab)
		[
			SNew(SDictionaryCreatorMainWindow)
		];
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDictionaryCreatorModule, DictionaryCreator)