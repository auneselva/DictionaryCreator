// Copyright https://github.com/auneselva

#include "DictionaryCreatorUtils.h"
#include "SDictionaryCreatorMainWindow.h"

#include "Policies/CondensedJsonPrintPolicy.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"
#include "DesktopPlatformModule.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Async/Async.h"

DEFINE_LOG_CATEGORY_STATIC(LogDictionaryCreatorUtils, Log, All);

const FString DictionaryCreatorUtils::ENTRY_KEY = TEXT("Key");
const FString DictionaryCreatorUtils::ENTRY_VALUE = TEXT("Value");

bool DictionaryCreatorUtils::ExportData(const FString& DataName, const TArray<TSharedPtr<FDictionaryElement>>& DataToExport)
{

	TMap<FString, FString> FilteredData = FilterData(DataToExport); 
	if (FilteredData.IsEmpty())
	{
		UE_LOG(LogDictionaryCreatorUtils, Warning, TEXT("No data to save!"));
		ShowNotification(FText::FromString("No data to save!"));
		return false;
	}
	
	FString JsonString;
	bool bSuccess = SerializeToJson(DataName, FilteredData, JsonString);
	if (!bSuccess)
	{
		UE_LOG(LogDictionaryCreatorUtils, Warning, TEXT("Failed to serialize data to JSON string!"));
		ShowNotification(FText::FromString("Failed to serialize data to JSON String!"));
		return false;
	}
	FString ResultFilename;
	bSuccess = SaveToFile(JsonString, ResultFilename);
	if (!bSuccess)
	{
		UE_LOG(LogDictionaryCreatorUtils, Warning, TEXT("Failed to save Json data to file!"));
		ShowNotification(FText::FromString("Failed to save Json data to file!"));
		return false;
	}

	ShowNotification(FText::FromString(TEXT("Successfully saved Json data to ")), FText::FromString(*ResultFilename));
	return true;
}

TMap<FString, FString> DictionaryCreatorUtils::FilterData(const TArray<TSharedPtr<FDictionaryElement>>& InDataToFilter)
{
	TMap<FString, FString> FilteredData;
	for (const TSharedPtr<FDictionaryElement> &Pair : InDataToFilter)
	{
		if (!Pair.IsValid() || Pair->Key.IsEmpty())
			continue;

		FilteredData.Emplace(Pair->Key, Pair->Value);
	}
	return FilteredData;
}

bool DictionaryCreatorUtils::SerializeToJson(const FString& DataName, const TMap<FString, FString>& InDataToSerialize, FString& OutSerializedData)
{
	TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	TArray<TSharedPtr<FJsonValue>> JsonValues;
	for (const TPair<FString, FString> &Pair : InDataToSerialize)
	{
		TSharedPtr< FJsonObject > Entry = MakeShared<FJsonObject>();
		Entry->SetStringField(ENTRY_KEY, Pair.Key);
		Entry->SetStringField(ENTRY_VALUE, Pair.Value);
		JsonValues.Emplace(MakeShared<FJsonValueObject>(Entry));
	}
	
	JsonObject->SetArrayField(DataName, JsonValues);
	TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&OutSerializedData);
	return FJsonSerializer::Serialize(JsonObject, Writer); 
	
}

bool DictionaryCreatorUtils::SaveToFile(const FString& DataJsonString, FString& OutFilename)
{
	const FString FileTypes = TEXT("JSON Files (*.json)|*.json");
	const FString DefaultFilename = TEXT("Dictionary_");
	TArray<FString> OutSaveFileNames;
	const void* ParentWindowWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	
	const FString DefaultOutputDirectory = FPaths::Combine(*FPaths::ProjectSavedDir(), TEXT("DictionaryCreator"));
	if (!PlatformFile.DirectoryExists(*DefaultOutputDirectory))
	{
		PlatformFile.CreateDirectoryTree(*DefaultOutputDirectory);
	}
	
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	const bool bFileSelected = DesktopPlatform->SaveFileDialog(
		ParentWindowWindowHandle,
		TEXT("Save file"),
		DefaultOutputDirectory,
		DefaultFilename,
		FileTypes,
		EFileDialogFlags::None,
		OutSaveFileNames);
	
	if (bFileSelected && OutSaveFileNames.Num() > 0)
	{
		OutFilename = OutSaveFileNames[0];
		return FFileHelper::SaveStringToFile(DataJsonString, *OutSaveFileNames[0]);
	}
	return false;
}

void DictionaryCreatorUtils::ShowNotification(const FText& InfoText, const FText& HyperLinkText, float Duration)
{
	Async(EAsyncExecution::TaskGraphMainThread, [InfoText, HyperLinkText, Duration]()
	{
		FNotificationInfo Info(FText::Format(InfoText, HyperLinkText));
		Info.ExpireDuration = Duration;
		if (!HyperLinkText.IsEmpty())
		{
			Info.HyperlinkText = HyperLinkText;
			Info.Hyperlink = FSimpleDelegate::CreateLambda([HyperLinkText]() { FPlatformProcess::ExploreFolder(*HyperLinkText.ToString()); });
		}
		FSlateNotificationManager::Get().AddNotification(Info);
	});
}