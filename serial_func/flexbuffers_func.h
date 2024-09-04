#include <flatbuffers/flexbuffers.h>
#include "benchmark_struct.h"

namespace flex {
    size_t Serialize(const testData& data, std::vector<char> &serializedData) {
        flexbuffers::Builder builder;

        builder.Map([&]() {
        });
            builder.Finish();
            std::vector<uint8_t> outBuffer;
            outBuffer = builder.GetBuffer();
            serializedData.resize(outBuffer.size());
            std::memcpy(serializedData.data(), outBuffer.data(), outBuffer.size());
            return outBuffer.size();
        }
        void Deserialize(testData& data, std::vector<char> &serializedData, const size_t size) {
            auto root = flexbuffers::GetRoot(reinterpret_cast<const uint8_t*>(serializedData.data()), size).AsMap();

    }
    }
    