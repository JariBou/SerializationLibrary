#include <SerializationLib/Deserializer.h>
#include <iostream>


namespace Serialization {

	Deserializer::Deserializer(const std::filesystem::path& path) : BinaryStreamReader(path)
	{
	}

	inline bool Deserializer::ReadSerializableObject(Serialization::SerializableObject& targetObj) {
		targetObj.Deserialize(this);
		return true;
	}

}