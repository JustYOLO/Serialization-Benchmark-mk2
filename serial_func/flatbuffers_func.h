#include <flatbuffers/flatbuffers.h>
#include <vector>
#include "benchmark_struct.h"
#include "../schema/struct_generated.h"

namespace flat {
    size_t Serialize(const testData& data, std::vector<char> &serializedData) {
        flatbuffers::FlatBufferBuilder builder;
        std::vector<flatbuffers::Offset<fNested>> nested;
        for (int i = 0; i < 3; i++) {
            auto nestedData = CreatefNested(builder, data.jmihzbsn[i].tkuuzxpp, data.jmihzbsn[i].raxmltsa, data.jmihzbsn[i].bfabwiyj, data.jmihzbsn[i].zlvlpass, builder.CreateString(data.jmihzbsn[i].zwdygjzg), builder.CreateString(data.jmihzbsn[i].hlirxqvq));
            nested.push_back(nestedData);
        }
        auto result = CreateflatData(builder, data.wfxtqnoc, data.xzepbayf, data.wllldavf, data.todnlesm, builder.CreateString(data.ahpotwhv), builder.CreateString(data.jnxqcwxf), builder.CreateVector(nested));

        builder.Finish(result);
        serializedData.resize(builder.GetSize());
        std::memcpy(serializedData.data(), builder.GetBufferPointer(), builder.GetSize());
        return builder.GetSize();
    }
    
    void Deserialize(testData& data, std::vector<char> &serializedData, const size_t size) {
        auto flatData = GetflatData(serializedData.data());
        data.wfxtqnoc = flatData->wfxtqnoc();
        data.xzepbayf = flatData->xzepbayf();
        data.wllldavf = flatData->wllldavf();
        data.todnlesm = flatData->todnlesm();
        data.ahpotwhv = flatData->ahpotwhv()->c_str();
        data.jnxqcwxf = flatData->jnxqcwxf()->c_str();
        for(int i = 0; i < 3; i++) {
            data.jmihzbsn[i].tkuuzxpp = flatData->jmihzbsn()->Get(i)->tkuuzxpp();
            data.jmihzbsn[i].raxmltsa = flatData->jmihzbsn()->Get(i)->raxmltsa();
            data.jmihzbsn[i].bfabwiyj = flatData->jmihzbsn()->Get(i)->bfabwiyj();
            data.jmihzbsn[i].zlvlpass = flatData->jmihzbsn()->Get(i)->zlvlpass();
            data.jmihzbsn[i].zwdygjzg = flatData->jmihzbsn()->Get(i)->zwdygjzg()->c_str();
            data.jmihzbsn[i].hlirxqvq = flatData->jmihzbsn()->Get(i)->hlirxqvq()->c_str();
        }
        // in case of strings:
        //  data.{keys} = flatData->{keys}()->c_str();
    }
}
