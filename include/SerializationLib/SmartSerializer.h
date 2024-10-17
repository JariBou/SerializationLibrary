#pragma once
#include "SerializationLibrary.h"
#include "SerializableObject.h"

namespace Serialization
{
	class SERIAL_API SmartSerializer : public Serializer
	{
		public:
			SmartSerializer() = default;
			SmartSerializer(const SmartSerializer&) = delete;
			SmartSerializer(SmartSerializer&&) = delete;
			~SmartSerializer() = default;

			bool WriteSerializableObject(const Serialization::SerializableObject& obj) override;

			SmartSerializer& operator=(const SmartSerializer&) = delete;
			SmartSerializer& operator=(SmartSerializer&&) = delete;

		private:
	};
}
