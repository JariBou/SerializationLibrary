#include <SerializationLib/SmartSerializer.h>

namespace Serialization
{
	SmartSerializer::SmartSerializer(const std::filesystem::path& path) : Serializer(path)
	{
	}

	bool SmartSerializer::WriteSerializableObject(const Serialization::SerializableObject& obj)
	{
		return WriteSerializableObjectWithKey(obj, obj.GetUID());
	}
	bool SmartSerializer::WriteSerializableObjectWithKey(const Serialization::SerializableObject& obj, std::string key)
	{
		WriteString(key);

		uint64_t startObjStreamPosition = GetStreamPosition();
		size_t size = 0;
		WriteData((char*)&size, sizeof(size_t));

		obj.Serialize(this);

		uint64_t endStreamPosition = GetStreamPosition();
		size = endStreamPosition - startObjStreamPosition;

		SetStreamPosition(startObjStreamPosition);
		WriteData((char*)&size, sizeof(size_t));
		SetStreamPosition(endStreamPosition);

		return true;
	}
}
