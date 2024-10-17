#pragma once
#include "SerializationLibrary.h"
#include "SerializableObject.h"

namespace Serialization
{
	class SERIAL_API SmartDeserializer : public Deserializer
	{
		public:
			SmartDeserializer(const std::filesystem::path& path);

			SmartDeserializer(const SmartDeserializer&) = delete;
			SmartDeserializer(SmartDeserializer&&) = delete;
			~SmartDeserializer() = default;

			bool ReadSerializableObject(Serialization::SerializableObject& targetObj) override;
			
			bool ReadSerializableObjectWithKey(Serialization::SerializableObject& targetObj, std::string key);

			SmartDeserializer& operator=(const SmartDeserializer&) = delete;
			SmartDeserializer& operator=(SmartDeserializer&&) = delete;

		private:
	};
}
