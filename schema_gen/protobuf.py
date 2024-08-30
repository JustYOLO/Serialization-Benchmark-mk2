class protobuf_gen:
    def __init__(self, nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, key_value_pair, testSize) -> None:
        self.nkey = nkey
        self.tkey = tkey
        self.skeyMin = skeyMin
        self.skeyMax = skeyMax
        self.svalMin = svalMin
        self.svalMax = svalMax
        self.key_value_pair = key_value_pair
        self.testSize = testSize

    def gen_schema(self) -> str:
        content = """syntax = "proto3";

message ProtoData {
"""
        if self.tkey == "string":
            for idx, key in enumerate(self.key_value_pair.keys()):
                content += f"    string {key} = {idx + 1};\n"
        elif self.tkey == "int32_t":
            for idx, key in enumerate(self.key_value_pair.keys()):
                content += f"    int32 {key} = {idx + 1};\n"
        elif self.tkey == "double":
            for idx, key in enumerate(self.key_value_pair.keys()):
                content += f"    double {key} = {idx + 1};\n"
        content += "}\n"

        return content

    def gen_header(self) -> str:
        content = """#include "benchmark_struct.h"
#include "../schema/ProtoData.pb.h"

namespace proto {
    size_t Serialize(const testData& data, std::vector<char> &serializedData) {
        GOOGLE_PROTOBUF_VERIFY_VERSION; // is it necessary?
        ProtoData protoData;
"""
        for key in self.key_value_pair.keys():
            content += f"        protoData.set_{key}(data.{key});\n"

        content += """        size_t size = protoData.ByteSizeLong();
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
"""
        for key in self.key_value_pair.keys():
            content += f"        data.{key} = protoData.{key}();\n"
        content += """    }
    }
"""
        return content