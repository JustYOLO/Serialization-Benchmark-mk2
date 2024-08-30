#include "benchmark_struct.h"
#include "../schema/ProtoData.pb.h"

namespace proto {
    size_t Serialize(const testData& data, std::vector<char> &serializedData) {
        GOOGLE_PROTOBUF_VERIFY_VERSION; // is it necessary?
        ProtoData protoData;
        protoData.set_zvtecooq(data.zvtecooq);
        protoData.set_yhavzzus(data.yhavzzus);
        protoData.set_bdarcopv(data.bdarcopv);
        protoData.set_zyxhbtad(data.zyxhbtad);
        protoData.set_bifsqzpy(data.bifsqzpy);
        protoData.set_wpeblhba(data.wpeblhba);
        protoData.set_eqohxbbj(data.eqohxbbj);
        protoData.set_rgmckfxb(data.rgmckfxb);
        size_t size = protoData.ByteSizeLong();
            serializedData.resize(size);
            protoData.SerializeToArray(serializedData.data(), static_cast<int>(size));
            // protoData.SerializeToArray(buffer.data(), static_cast<int>(size));
            // std::ofstream output(filename, std::ios::out | std::ios::binary);
            // if (!protoData.SerializeToOstream(&output)) {
            //     std::cerr << "protobuf: Failed to write data to file." << std::endl;
            // }
            return size;
        }
        void Deserialize(testData& data, std::vector<char> &serializedData, const size_t size) {
            ProtoData protoData;
            protoData.ParseFromArray(serializedData.data(), static_cast<int>(size));
        data.zvtecooq = protoData.zvtecooq();
        data.yhavzzus = protoData.yhavzzus();
        data.bdarcopv = protoData.bdarcopv();
        data.zyxhbtad = protoData.zyxhbtad();
        data.bifsqzpy = protoData.bifsqzpy();
        data.wpeblhba = protoData.wpeblhba();
        data.eqohxbbj = protoData.eqohxbbj();
        data.rgmckfxb = protoData.rgmckfxb();
    }
    }
