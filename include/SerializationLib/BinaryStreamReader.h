#pragma once
#include "SerializationLibrary.h"

#include "SerializableObject.h"

#include <filesystem>
#include <fstream>
#include <map>
#include <iostream>
#include <type_traits>

namespace Serialization
{

	class SERIAL_API BinaryStreamReader
	{

		public:
			BinaryStreamReader(const std::filesystem::path& path);
			virtual ~BinaryStreamReader();
			void Close();

			bool IsStreamGood() const;
			uint64_t GetStreamPosition();
			void SetStreamPosition(uint64_t position);

			bool ReadData(char* destination, size_t size);

			bool ReadString(std::string& target);

			virtual bool ReadSerializableObject(Serialization::SerializableObject& targetObj) = 0;

			// Ok so templates need to go on the .h
			template<typename T>
			bool ReadObject(T& target) {
				if constexpr (std::is_base_of_v<std::string, T>) {
					ReadString(target);
				}
				else if constexpr (std::is_base_of_v<Serialization::SerializableObject, T>) {
					ReadSerializableObject(target);
				}
				else if constexpr (std::is_trivial<T>()) {
					ReadRaw<T>(target);
				}
				else {
					ReadRaw<T>(target);
					//ReadObject<Key>(key);
				}
				return true;
			}

			template<typename T>
			bool ReadRaw(T& target) {
				ReadData((char*)&target, sizeof(T));
				return true;
			}

			

			template<typename Key, typename Value>
			void ReadMap(std::map<Key, Value>& map) {
				// Write size of map
				uint32_t size = 0;
				ReadRaw<uint32_t>(size);

				for (uint32_t i = 0; i < size; i++) {
					// Ok so if one of the types is a string if goes to shit
					Key key{};

					ReadObject<Key>(key);
					ReadObject<Value>(map[key]);

					//map[key] = value;
				}
			}

			template<typename T>
			void ReadVector(std::vector<T>& vector) {
				// Write the size of the array
				uint32_t size = 0;
				ReadRaw<uint32_t>(size);
				vector.resize(size);

				for (uint32_t i = 0; i < size; i++) {
					T value{};
					ReadObject<T>(value);
					vector[i] = value;
				}
			}


		private:
			std::filesystem::path m_Path;
			std::ifstream m_Stream;

	};
}

//#include "BinaryStreamReader.inl"

