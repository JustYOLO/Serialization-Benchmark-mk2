#include "benchmark_struct.h"
#include "../schema/ProtoData.pb.h"

namespace proto {
    size_t Serialize(const testData& data, std::vector<char> &serializedData) {
        GOOGLE_PROTOBUF_VERIFY_VERSION; // is it necessary?
        ProtoData protoData;
            protoData.set_struct(data.struct);
            protoData.set_mjogvdtj(data.mjogvdtj);
            protoData.set_int(data.int);
            protoData.set_float(data.float);
            protoData.set_string(data.string);
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
            data.struct = protoData.struct();
            data.mjogvdtj = protoData.mjogvdtj();
            data.int = protoData.int();
            data.float = protoData.float();
            data.string = protoData.string();
    }
}
