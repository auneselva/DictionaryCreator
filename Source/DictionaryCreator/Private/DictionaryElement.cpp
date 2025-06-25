
#include "DictionaryElement.h"

void FDictionaryElement::UpdateDataArrayKey(const FText& NewKey)
{
	Key = NewKey.ToString();
}

void FDictionaryElement::UpdateDataArrayValue(const FText& NewValue)
{
	Value = NewValue.ToString();
}
