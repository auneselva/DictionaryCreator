// by Agnieszka Konopka, May 2025.

#pragma once

class DICTIONARYCREATOR_API DictionaryCreatorUtils
{
public:
	/*
	* Exports data to Json format and saves file in the location specified by user. Duplicate keys are omitted.
	*/
	static bool ExportData(const FString& DataName, TArray<TPair<FString, FString>>& InDataToExport);

	/*
	 * Filters data by skipping pairs with empty keys and omits duplicates by putting into a TMap.
	 */
	static TMap<FString, FString> FilterData(TArray<TPair<FString, FString>>& InDataToFilter);
	static bool SerializeToJson(const FString& DataName, TMap<FString, FString>& InDataToSerialize, FString& OutSerializedData);
	static bool SaveToFile(const FString& DataJsonString,  FString& OutFilename);
	static void ShowNotification(const FText& Text, float Duration = 8.0f);
	
protected:
	static const FString ENTRY_KEY;
	static const FString ENTRY_VALUE;
	
};
