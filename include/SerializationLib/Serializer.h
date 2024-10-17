#pragma once

#include "SerializationLibrary.h"
#include <filesystem>
#include "BinaryStreamWriter.h"

namespace Serialization
{

	class SERIAL_API Serializer : public BinaryStreamWriter
	{

		public:
			Serializer(const std::filesystem::path& path);

			bool WriteSerializableObject(const Serialization::SerializableObject& obj) override;
	};

}
