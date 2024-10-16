#include <SerializationLib/BinaryStreamReader.h>

namespace Serialization
{
	BinaryStreamReader::BinaryStreamReader(const std::filesystem::path& path) : m_Path(path)
	{
#if IsEditor
		m_Stream = std::ifstream(path, std::ifstream::in | std::ifstream::binary);
#else
		m_Stream = std::ifstream(path, std::ifstream::in | std::ifstream::binary);
#endif
	}

	BinaryStreamReader::~BinaryStreamReader()
	{
		Close();
	}

	void BinaryStreamReader::Close()
	{
		m_Stream.close();
	}

	bool BinaryStreamReader::IsStreamGood() const
	{
		return m_Stream.good();
	}

	uint64_t BinaryStreamReader::GetStreamPosition()
	{
		return m_Stream.tellg();
	}

	void BinaryStreamReader::SetStreamPosition(uint64_t position)
	{
		m_Stream.seekg(position);
	}

	bool BinaryStreamReader::ReadData(char* destination, size_t size)
	{
		m_Stream.read(destination, size);
		return true;
	}

	bool BinaryStreamReader::ReadString(std::string& target)
	{
		size_t size = 0;

		ReadData((char*)&size, sizeof(size_t));
		target.resize(size);
		bool success = ReadData((char*)target.data(), sizeof(char) * size);

		return true;
	}
}