#include <flatbuffers/flexbuffers.h>
#include "benchmark_struct.h"

namespace flex {
    size_t Serialize(const testData& data, std::vector<char> &serializedData) {
        flexbuffers::Builder builder;

        builder.Map([&]() {
            builder.String("zvtecooq", data.zvtecooq);
            builder.String("yhavzzus", data.yhavzzus);
            builder.String("bdarcopv", data.bdarcopv);
            builder.String("zyxhbtad", data.zyxhbtad);
            builder.String("bifsqzpy", data.bifsqzpy);
            builder.String("wpeblhba", data.wpeblhba);
            builder.String("eqohxbbj", data.eqohxbbj);
            builder.String("rgmckfxb", data.rgmckfxb);
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

            data.zvtecooq = root["zvtecooq"].AsString().str();
        data.yhavzzus = root["yhavzzus"].AsString().str();
        data.bdarcopv = root["bdarcopv"].AsString().str();
        data.zyxhbtad = root["zyxhbtad"].AsString().str();
        data.bifsqzpy = root["bifsqzpy"].AsString().str();
        data.wpeblhba = root["wpeblhba"].AsString().str();
        data.eqohxbbj = root["eqohxbbj"].AsString().str();
        data.rgmckfxb = root["rgmckfxb"].AsString().str();
    }
    }
    