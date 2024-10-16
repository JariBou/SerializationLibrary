#pragma once
#include "SerializationLibrary.h"
#include "BinaryStreamReader.h"

namespace Serialization 
{

    class SERIAL_API Deserializer : public BinaryStreamReader
    {
		public:
			Deserializer(const std::filesystem::path& path);

			bool ReadSerializableObject(Serialization::SerializableObject& targetObj) override;
			
    };
}

