#pragma once
#include "SerializationLibrary.h"
#include "SerializableObject.h"

namespace Serialization
{
	class SERIAL_API SmartSerializer : public Serializer
	{
		public:
			SmartSerializer(const std::filesystem::path& path);

			SmartSerializer(const SmartSerializer&) = delete;
			SmartSerializer(SmartSerializer&&) = delete;
			~SmartSerializer() = default;

			bool WriteSerializableObject(const Serialization::SerializableObject& obj) override;

			bool WriteSerializableObjectWithKey(const Serialization::SerializableObject& obj, std::string key);

			SmartSerializer& operator=(const SmartSerializer&) = delete;
			SmartSerializer& operator=(SmartSerializer&&) = delete;

		private:
	};
}
