#pragma once
#include "SerializationLibrary.h"

#include <filesystem>
#include <fstream>
#include <map>
#include <vector>

namespace Serialization 
{

	class SerializableObject;

	class SERIAL_API BinaryStreamWriter
	{

	public:
		BinaryStreamWriter(const std::filesystem::path& path);
		virtual ~BinaryStreamWriter();
		void Close();

		bool IsStreamGood() const;
		uint64_t GetStreamPosition();
		void SetStreamPosition(uint64_t position);

		bool WriteData(const char* data, size_t size);

		bool WriteString(const std::string content);

		// Ok so templates need to go on the .h

		template<typename T>
		bool WriteObject(const T& value) {
			if constexpr (std::is_base_of_v<std::string, T>) {
				WriteString(value);
			}
			else if constexpr (std::is_base_of_v<Serialization::SerializableObject, T>) {
				WriteSerializableObject(value);
			}
			else if constexpr (std::is_trivial<T>()) {
				WriteRaw<T>(value);
			}
			else {
				WriteRaw<T>(value);
				//WriteObject<Key>(key);
			}
			return true;
		}


		template<typename T>
		bool WriteRaw(const T& content) {
			WriteData((char*)&content, sizeof(T));
			return true;
		}

		virtual bool WriteSerializableObject(const Serialization::SerializableObject& obj) = 0;

		template<typename Key, typename Value>
		void WriteMap(const std::map<Key, Value>& map)
		{
			// Write size of map
			WriteRaw<uint32_t>((uint32_t)map.size());

			for (const auto& [key, value] : map)
			{
				WriteObject<Key>(key);
				WriteObject<Value>(value);
			}

		}

		template<typename T>
		void WriteVector(const std::vector<T>& vector) {
			// Write the size of the array
			WriteRaw<uint32_t>((uint32_t)vector.size());

			for (const T& value : vector) {
				WriteObject<T>(value);
			}
		}

	private:
		std::filesystem::path m_Path;
		std::ofstream m_Stream;

	};
}

//#include "BinaryStreamWriter.inl"

