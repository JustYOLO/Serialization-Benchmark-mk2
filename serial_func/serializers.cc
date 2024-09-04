#include <benchmark/benchmark.h>
#include "serializers.h"
// #include "flexbuffers_func.h"
// #include "protobuf_func.h"
// #include "thrift_func.h"
#include "flatbuffers_func.h"
// #include "json_func.h"

namespace serializers {

    size_t serializeMsgPack(const testData& data, std::vector<char> &serializedData) {
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, data);

        serializedData.resize(sbuf.size());
        std::memcpy(serializedData.data(), sbuf.data(), sbuf.size());
        return sbuf.size();
    }

    testData deserializeMsgPack(std::vector<char> &serializedData, size_t size) {
        msgpack::object_handle oh = msgpack::unpack(serializedData.data(), size);
        testData result;
        oh.get().convert(result);

        return result;
    }

    // size_t serializeProtoBuf(const testData& data, std::vector<char> &serializedData) {
    //     size_t size = proto::Serialize(data, serializedData);
    //     return size;
    // }
    // testData deserializeProtoBuf(std::vector<char> &serializedData, size_t size) {
    //     testData result;
    //     proto::Deserialize(result, serializedData, size);
    //     return result;
    // }

    // size_t serializeJson(const testData& data, std::vector<char> &serializedData) {
    //     size_t size = json::Serialize(data, serializedData);
    //     return size;
    // }

    // testData deserializeJson(std::vector<char> &serializedData, size_t size) {
    //     testData result;
    //     json::Deserialize(result, serializedData, size);
    //     return result;
    // }

    // size_t serializeFlexBuffers(const testData& data, std::vector<char> &serializedData) {
    //     size_t size = flex::Serialize(data, serializedData);
    //     return size;
    // }

    // testData deserializeFlexBuffers(std::vector<char> &serializedData, size_t size) {
    //     testData result;
    //     flex::Deserialize(result, serializedData, size);
    //     return result;
    // }

    // size_t serializeApacheThrift(const testData& data, std::vector<char> &serializedData) {
    //     size_t size = thrift::Serialize(data, serializedData);
    //     // state.PauseTiming();
    //     // std::ofstream outFile(filename, std::ios::binary);
    //     // outFile.write(serialized_str.c_str(), serialized_str.length());
    //     // outFile.close();
    //     return size;
    // }

    // testData deserializeApacheThrift(std::vector<char> &serializedData, size_t size) {
    //     testData data;
    //     thrift::Deserialize(data, serializedData, size);
    //     return data;
    // }

    size_t serializeFlatBuffers(const testData& data, std::vector<char> &serializedData) {
        return flat::Serialize(data, serializedData);
    }

    testData deserializeFlatBuffers(std::vector<char> &serializedData, size_t size) {
        testData data;
        flat::Deserialize(data, serializedData, size);
        return data;
    }

}  // namespace serializers