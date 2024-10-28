#include <SerializationLib/SmartDeserializer.h>

namespace Serialization
{
    SmartDeserializer::SmartDeserializer(const std::filesystem::path& path) : Deserializer(path)
    {
    }

    bool SmartDeserializer::ReadSerializableObject(Serialization::SerializableObject& obj)
    {


        return false;
    }
    bool SmartDeserializer::ReadSerializableObjectWithKey(Serialization::SerializableObject& targetObj, std::string key)
    {
        SetStreamPosition(0);
        while (IsStreamGood()) {
			std::string readKey;
			ReadString(readKey);

            uint64_t startObjStreamPosition = GetStreamPosition();
			size_t size = 0;
			ReadRaw(size);

			if (readKey == key) {
				targetObj.Deserialize(this);
				return true;
            }
            else {
                SetStreamPosition(startObjStreamPosition + size);
            }
        }
        


        return false;
    }
}
