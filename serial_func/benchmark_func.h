#include <benchmark/benchmark.h>
#include <msgpack.hpp>
#include "serializers.h"
#include "benchmark_struct.h"

static void BM_MsgPackSerialization(benchmark::State& state, testData data, std::vector<char> &serializedData, size_t &size) {
    size_t dataSize = sizeof(data);
    for (auto _ : state) {
        auto serialized = serializers::serializeMsgPack(data, serializedData);
        benchmark::DoNotOptimize(serialized);
        size = serialized;
    }
    state.SetLabel(std::to_string(dataSize) + " " + std::to_string(size));
}

static void BM_MsgPackDeserialization(benchmark::State& state, std::vector<char> &serializedData, size_t &size) {
    for (auto _ : state) {
        auto deserialized = serializers::deserializeMsgPack(serializedData, size);
        benchmark::DoNotOptimize(deserialized);
    }
}

// static void BM_ProtoBufSerialization(benchmark::State& state, testData data, std::vector<char> &serializedData, size_t &size) {
//     size_t dataSize = sizeof(data);
//     for (auto _ : state) {
//         auto serialized = serializers::serializeProtoBuf(data, serializedData);
//         benchmark::DoNotOptimize(serialized);
//         size = serialized;
//     }
//     state.SetLabel(std::to_string(dataSize) + " " + std::to_string(size));
// }

// static void BM_ProtoBufDeserialization(benchmark::State& state, std::vector<char> &serializiedData, size_t &size) {
//     for (auto _ : state) {
//         auto deserialized = serializers::deserializeProtoBuf(serializiedData, size);
//         benchmark::DoNotOptimize(deserialized);
//     }
// }

// static void BM_FlexBufSerialization(benchmark::State& state, testData data, std::vector<char> &serializedData, size_t &size) {
//     size_t dataSize = sizeof(data);
//     for (auto _ : state) {
//         auto serialized = serializers::serializeFlexBuffers(data, serializedData);
//         benchmark::DoNotOptimize(serialized);
//         size = serialized;
//     }
//     state.SetLabel(std::to_string(dataSize) + " " + std::to_string(size));

// }
// static void BM_FlexBufDeserialization(benchmark::State& state, std::vector<char> &serializiedData, size_t &size) {
//     for (auto _ : state) {
//         auto deserialized = serializers::deserializeFlexBuffers(serializiedData, size);
//         benchmark::DoNotOptimize(deserialized);
//     }
// }

// static void BM_ThriftSerialization(benchmark::State& state, testData data, std::vector<char> &serializedData, size_t &size) {
//     size_t dataSize = sizeof(data);
//     for (auto _ : state) {
//         auto serialized = serializers::serializeApacheThrift(data, serializedData);
//         benchmark::DoNotOptimize(serialized);
//         size = serialized;
//     }
//     state.SetLabel(std::to_string(dataSize) + " " + std::to_string(size));

// }
// static void BM_ThriftDeserialization(benchmark::State& state, std::vector<char> &serializedData, size_t &size) {
//     for (auto _ : state) {
//         auto deserialized = serializers::deserializeApacheThrift(serializedData, size);
//         benchmark::DoNotOptimize(deserialized);
//     }
// }

static void BM_FlatBufSerialization(benchmark::State& state, testData data, std::vector<char> &serializedData, size_t &size) {
    size_t dataSize = sizeof(data);
    for (auto _ : state) {
        auto serialized = serializers::serializeFlatBuffers(data, serializedData);
        benchmark::DoNotOptimize(serialized);
        size = serialized;
    }
    state.SetLabel(std::to_string(dataSize) + " " + std::to_string(size));
}

static void BM_FlatBufDeserialization(benchmark::State& state, std::vector<char> &serializedData, size_t &size) {
    for (auto _ : state) {
        auto deserialized = serializers::deserializeFlatBuffers(serializedData, size);
        benchmark::DoNotOptimize(deserialized);
    }
}

// static void BM_JsonSerialization(benchmark::State& state, testData data, std::vector<char> &serializedData, size_t &size) {
//     size_t dataSize = sizeof(data);
//     for (auto _ : state) {
//         auto serialized = serializers::serializeJson(data, serializedData);
//         benchmark::DoNotOptimize(serialized);
//         size = serialized;
//     }
//     state.SetLabel(std::to_string(dataSize) + " " + std::to_string(size));
// }

// static void BM_JsonDeserialization(benchmark::State& state, std::vector<char> &serializedData, size_t &size) {
//     for (auto _ : state) {
//         auto deserialized = serializers::deserializeJson(serializedData, size);
//         benchmark::DoNotOptimize(deserialized);
//     }
// }
