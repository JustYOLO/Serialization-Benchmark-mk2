#include <flatbuffers/flatbuffers.h>
#include <vector>
#include "benchmark_struct.h"
#include "../schema/struct_generated.h"

namespace flat {
    size_t Serialize(const testData& data, std::vector<char> &serializedData) {
        flatbuffers::FlatBufferBuilder builder;
        std::vector<flatbuffers::Offset<flatbuffers::String>> keys;
        keys.push_back(builder.CreateString(data.zvtecooq));
        keys.push_back(builder.CreateString(data.yhavzzus));
        keys.push_back(builder.CreateString(data.bdarcopv));
        keys.push_back(builder.CreateString(data.zyxhbtad));
        keys.push_back(builder.CreateString(data.bifsqzpy));
        keys.push_back(builder.CreateString(data.wpeblhba));
        keys.push_back(builder.CreateString(data.eqohxbbj));
        keys.push_back(builder.CreateString(data.rgmckfxb));
        auto result = CreateflatData(builder, keys[0], keys[1], keys[2], keys[3], keys[4], keys[5], keys[6], keys[7]);
        builder.Finish(result);
        serializedData.resize(builder.GetSize());
        std::memcpy(serializedData.data(), builder.GetBufferPointer(), builder.GetSize());
        return builder.GetSize();
    }
    
    void Deserialize(testData& data, std::vector<char> &serializedData, const size_t size) {
        auto flatData = GetflatData(serializedData.data());
        data.zvtecooq = flatData->zvtecooq()->str();
        data.yhavzzus = flatData->yhavzzus()->str();
        data.bdarcopv = flatData->bdarcopv()->str();
        data.zyxhbtad = flatData->zyxhbtad()->str();
        data.bifsqzpy = flatData->bifsqzpy()->str();
        data.wpeblhba = flatData->wpeblhba()->str();
        data.eqohxbbj = flatData->eqohxbbj()->str();
        data.rgmckfxb = flatData->rgmckfxb()->str();
        // data.{keys} = flatData->{keys}()->c_str();
    }
}
