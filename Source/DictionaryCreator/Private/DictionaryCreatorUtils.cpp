// by Agnieszka Konopka, May 2025.

#include "DictionaryCreatorUtils.h"
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

bool DictionaryCreatorUtils::ExportData(const FString& DataName, TArray<TPair<FString, FString>>& DataToExport)
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

	ShowNotification(FText::FromString(FString::Format(TEXT("Successfully saved Json data to {0}!"), {*ResultFilename})));
	return true;
}


TMap<FString, FString> DictionaryCreatorUtils::FilterData(TArray<TPair<FString, FString>>& InDataToFilter)
{
	TMap<FString, FString> FilteredData;
	for (TPair<FString, FString> &Pair : InDataToFilter)
	{
		if (Pair.Key.IsEmpty())
			continue;

		FilteredData.Emplace(Pair.Key, Pair.Value);
	}
	return FilteredData;
}

bool DictionaryCreatorUtils::SerializeToJson(const FString& DataName, TMap<FString, FString>& InDataToSerialize, FString& OutSerializedData)
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

	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	const void* ParentWindowWindowHandle = FSlateApplication::Get().FindBestParentWindowHandleForDialogs(nullptr);

	const bool bFileSelected = DesktopPlatform->SaveFileDialog(
		ParentWindowWindowHandle,
		TEXT("Save file"),
		FPaths::ProjectSavedDir(),
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
void DictionaryCreatorUtils::ShowNotification(const FText& Text, float Duration)
{
	Async(EAsyncExecution::TaskGraphMainThread, [Text, Duration]()
	{
		FNotificationInfo Info(Text);
		Info.ExpireDuration = Duration;
		FSlateNotificationManager::Get().AddNotification(Info);
	});
}