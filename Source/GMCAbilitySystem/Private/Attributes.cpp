﻿#include "Attributes.h"

UGMCAttributeSet::UGMCAttributeSet()
{
}

FAttribute* UGMCAttributeSet::GetAttributeByName(FName PropName)
{
	FProperty* Property = GetClass()->FindPropertyByName(PropName);
	if (!Property) return nullptr;

	FStructProperty* StructProperty = CastField<FStructProperty>(Property);
	if (!StructProperty) return nullptr;

	FAttribute* Attribute = StructProperty->ContainerPtrToValuePtr<FAttribute>(this);
	if (Attribute == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("BadPointer | Couldn't Find: %s"), *PropName.ToString());
	}
	return Attribute;
}

TArray<FAttribute*> UGMCAttributeSet::GetAllAttributes()
{	
	TArray<FAttribute*> Attributes;
	for( TFieldIterator<FProperty> Attribute(GetClass()); Attribute; ++Attribute ) {
		Attributes.Push(Attribute->ContainerPtrToValuePtr<FAttribute>(this));
	}		
	return Attributes;
}
