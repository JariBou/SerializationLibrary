#include <SerializationLib/Serializer.h>

#include <SerializationLib/SerializableObject.h>

#include <iostream>
#include <string>

namespace Serialization 
{

	Serializer::Serializer(const std::filesystem::path& path) : BinaryStreamWriter(path)
	{
	}

	inline bool Serializer::WriteSerializableObject(const Serialization::SerializableObject& obj) {
		obj.Serialize(this);
		return true;
	}
	
}
