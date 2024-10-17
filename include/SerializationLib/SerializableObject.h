#pragma once
#include "Serializer.h"
#include "Deserializer.h"
#include "SerializationLibrary.h"
//TODO check if maybe a forward declaration wouldn't be better

namespace Serialization
{
	class Serializer;
	class Deserializer;

	class SERIAL_API SerializableObject
	{

	public:
		void Serialize(Serialization::Serializer* serializer) const {
			OnSerialize(serializer);
		}
		void Deserialize(Serialization::Deserializer* deserializer) {
			OnDeserialize(deserializer);
		}
	
	protected:
		virtual void OnSerialize(Serialization::Serializer* serializer) const = 0;
		virtual void OnDeserialize(Serialization::Deserializer* deserializer) = 0;

	};
}

