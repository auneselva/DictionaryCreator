// by Agnieszka Konopka, May 2025.

#pragma once

#include "DictionaryElement.h"

class DICTIONARYCREATOR_API DictionaryCreatorUtils
{
public:
	/*
	* Exports data to Json format and saves file in the location specified by user. Duplicate keys are omitted.
	*/
	static bool ExportData(const FString& DataName, const TArray<TSharedPtr<FDictionaryElement>>& InDataToExport);

	/*
	 * Filters data by skipping pairs with empty keys and omits duplicates by putting into a TMap.
	 */
	static TMap<FString, FString> FilterData(const TArray<TSharedPtr<FDictionaryElement>>& InDataToFilter);
	static bool SerializeToJson(const FString& DataName, const TMap<FString, FString>& InDataToSerialize, FString& OutSerializedData);
	static bool SaveToFile(const FString& DataJsonString,  FString& OutFilename);
	static void ShowNotification(const FText& Text, const FText& HyperLinkText = FText::GetEmpty(), float Duration = 8.0f);
	
protected:
	static const FString ENTRY_KEY;
	static const FString ENTRY_VALUE;
	
};
