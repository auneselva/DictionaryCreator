#pragma once
#include "DictionaryElement.generated.h"

USTRUCT(BlueprintType)
struct FDictionaryElement
{
	GENERATED_BODY()
	
	FString Key;
	FString Value;
	
	FDictionaryElement(FString Key = TEXT(""), FString Value = TEXT("") ):
	Key(Key),
	Value(Value) {}
	
	void UpdateDataArrayKey(const FText& NewKey);
	void UpdateDataArrayValue(const FText& NewValue);
};