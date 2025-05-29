#pragma once


class DICTIONARYCREATOR_API DictionaryCreatorUtils
{
public:
	static bool ExportData(TArray<TPair<FString, FString>>& InDataToExport);
	static TMap<FString, FString> FilterData(TArray<TPair<FString, FString>>& InDataToFilter);
	static bool SerializeToJson(TMap<FString, FString>& InDataToSerialize, FString& OutSerializedData);
	static bool SaveToFile(FString Data, FString Format);
	
};
