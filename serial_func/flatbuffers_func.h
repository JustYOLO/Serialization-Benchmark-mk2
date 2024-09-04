#include <flatbuffers/flatbuffers.h>
#include <vector>
#include "benchmark_struct.h"
#include "../schema/struct_generated.h"

namespace flat {
    size_t Serialize(const testData& data, std::vector<char> &serializedData) {
        flatbuffers::FlatBufferBuilder builder;
        std::vector<flatbuffers::Offset<fNested>> nested;
        for (int i = 0; i < 3; i++) {
            auto nestedData = CreatefNested(builder, data.mjogvdtj[i].etiizwwn, data.mjogvdtj[i].cbcfskih, data.mjogvdtj[i].ldeucjga, data.mjogvdtj[i].cgekyebx, builder.CreateString(data.mjogvdtj[i].xgrdxjrt), builder.CreateString(data.mjogvdtj[i].calizksb));
            nested.push_back(nestedData);
        }
        auto result = CreateflatData(builder, data.lmontiqn, data.gttsakbp, data.sgruersi, data.cbjiwmfv, builder.CreateString(data.toiywwtb), builder.CreateString(data.ojkinvvf), builder.CreateVector(nested));

        builder.Finish(result);
        serializedData.resize(builder.GetSize());
        std::memcpy(serializedData.data(), builder.GetBufferPointer(), builder.GetSize());
        return builder.GetSize();
    }
    
    void Deserialize(testData& data, std::vector<char> &serializedData, const size_t size) {
        auto flatData = GetflatData(serializedData.data());
        data.lmontiqn = flatData->lmontiqn();
        data.gttsakbp = flatData->gttsakbp();
        data.sgruersi = flatData->sgruersi();
        data.cbjiwmfv = flatData->cbjiwmfv();
        data.toiywwtb = flatData->toiywwtb()->c_str();
        data.ojkinvvf = flatData->ojkinvvf()->c_str();
        for(int i = 0; i < 3; i++) {
            data.mjogvdtj[i].etiizwwn = flatData->mjogvdtj()->Get(i)->etiizwwn();
            data.mjogvdtj[i].cbcfskih = flatData->mjogvdtj()->Get(i)->cbcfskih();
            data.mjogvdtj[i].ldeucjga = flatData->mjogvdtj()->Get(i)->ldeucjga();
            data.mjogvdtj[i].cgekyebx = flatData->mjogvdtj()->Get(i)->cgekyebx();
            data.mjogvdtj[i].xgrdxjrt = flatData->mjogvdtj()->Get(i)->xgrdxjrt()->c_str();
            data.mjogvdtj[i].calizksb = flatData->mjogvdtj()->Get(i)->calizksb()->c_str();
        }
        // in case of strings:
        //  data.{keys} = flatData->{keys}()->c_str();
    }
}
