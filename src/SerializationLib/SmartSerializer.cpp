#include <SerializationLib/SmartSerializer.h>

namespace Serialization
{
	bool SmartSerializer::WriteSerializableObject(const Serialization::SerializableObject& obj)
	{
		uint64_t startStreamPosition = GetStreamPosition();

		size_t size = 0;
		WriteData((char*)&size, sizeof(size_t));

		obj.Serialize(this);

		uint64_t endStreamPosition = GetStreamPosition();
		size = endStreamPosition - startStreamPosition;

		SetStreamPosition(startStreamPosition);
		WriteData((char*)&size, sizeof(size_t));
		SetStreamPosition(endStreamPosition);

		return true;
	}
}
