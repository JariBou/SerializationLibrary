#include <SerializationLib/SerializableObject.h>
#include <SerializationLib/SmartSerializer.h>
#include <SerializationLib/SmartDeserializer.h>

class SerializableTest : public Serialization::SerializableObject {
public:

	SerializableTest(std::string name, int age) : m_name(name), m_age(age) {}

	// Inherited via SerializableObject
	void OnSerialize(Serialization::Serializer* serializer) const override
	{
		serializer->WriteString(m_name);
		serializer->WriteRaw(m_age);
	}
	void OnDeserialize(Serialization::Deserializer* deserializer) override
	{
		deserializer->ReadString(m_name);
		deserializer->ReadRaw(m_age);
	}

	std::string GetUID() const override {
		return "SerializableTest(" + m_name + ")";
	}

	std::string m_name;
	int m_age;
};

int main() 
{
	SerializableTest st ("Jari", 20);
	SerializableTest st2 ("Jari2", 40);
	SerializableTest st3 ("James", 420);
	SerializableTest st4 ("Janus", 656);

	Serialization::SmartSerializer ss ("tests.dat");

	ss.WriteSerializableObjectWithKey(st, "player1");
	ss.WriteSerializableObjectWithKey(st2, "player2");
	ss.WriteSerializableObjectWithKey(st3, "player_that_loves");
	ss.WriteSerializableObjectWithKey(st4, "player_that_hates");

	ss.Close();

	Serialization::SmartDeserializer sd("tests.dat");

	SerializableTest dst1 ("", -1);
	sd.ReadSerializableObjectWithKey(dst1, "player_that_loves");

	std::cout << "Read Name => " << dst1.m_name << std::endl;
	std::cout << "Read Age => " << dst1.m_age << std::endl;

	sd.Close();


	return 0;
}