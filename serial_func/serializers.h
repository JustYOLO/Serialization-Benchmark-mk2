#include "benchmark_struct.h"
#include <vector>
#include <msgpack.hpp>
#include <fstream>

// Include headers for other serialization libraries here

namespace serializers {

// MessagePack
size_t serializeMsgPack(const testData& data, std::vector<char> &serializedData);
testData deserializeMsgPack(std::vector<char> &serializedData, size_t size);

// futher improvements add more serialization functions here

// Protobuf
size_t serializeProtoBuf(const testData& data, std::vector<char> &serializedData);
testData deserializeProtoBuf(std::vector<char> &serializedData, size_t size);

// JSON
size_t serializeJson(const testData& data, std::vector<char> &serializedData);
testData deserializeJson(std::vector<char> &serializedData, size_t size);

// FlexBuffers
size_t serializeFlexBuffers(const testData& data, std::vector<char> &serializedData);
testData deserializeFlexBuffers(std::vector<char> &serializedData, size_t size);

// Apache Thrift

size_t serializeApacheThrift(const testData& data, std::vector<char> &serializedData);
testData deserializeApacheThrift(std::vector<char> &serializedData, size_t size);

// FlatBuffers
size_t serializeFlatBuffers(const testData& data, std::vector<char> &serializedData);
testData deserializeFlatBuffers(std::vector<char> &serializedData, size_t size);

}  // namespace serializers