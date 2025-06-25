#pragma once
#include "DictionaryElement.generated.h"

USTRUCT(BlueprintType)
struct FDictionaryElement
{
	GENERATED_BODY()

	int Index;
	FString Key;
	FString Value;
	
	FDictionaryElement(int Index = 0, FString Key = TEXT(""), FString Value = TEXT("") ):
	Index(Index),
	Key(Key),
	Value(Value) {}
	
	void UpdateDataArrayKey(const FText& NewKey);
	void UpdateDataArrayValue(const FText& NewValue);
};