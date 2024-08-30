class flexbuf_gen:
    def __init__(self, nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, key_value_pair, testSize) -> None:
        self.nkey = nkey
        self.tkey = tkey
        self.skeyMin = skeyMin
        self.skeyMax = skeyMax
        self.svalMin = svalMin
        self.svalMax = svalMax
        self.key_value_pair = key_value_pair
        self.testSize = testSize

    def gen_header(self) -> str:
        header_content = """#include <flatbuffers/flexbuffers.h>
#include "benchmark_struct.h"

namespace flex {
    size_t Serialize(const testData& data, std::vector<char> &serializedData) {
        flexbuffers::Builder builder;

        builder.Map([&]() {
"""
        # builder.String("key", "value");
        if self.tkey == "string":
            for key in self.key_value_pair.keys():
                header_content += f"            builder.String(\"{key}\", data.{key});\n"
        elif self.tkey == "int32_t":
            for key in self.key_value_pair.keys():
                header_content += f"            builder.Int(\"{key}\", data.{key});\n"
        elif self.tkey == "double":
            for key in self.key_value_pair.keys():
                header_content += f"            builder.Double(\"{key}\", data.{key});\n"

        header_content += """        });
            builder.Finish();
            std::vector<uint8_t> outBuffer;
            outBuffer = builder.GetBuffer();
            serializedData.resize(outBuffer.size());
            std::memcpy(serializedData.data(), outBuffer.data(), outBuffer.size());
            return outBuffer.size();
        }
        void Deserialize(testData& data, std::vector<char> &serializedData, const size_t size) {
            auto root = flexbuffers::GetRoot(reinterpret_cast<const uint8_t*>(serializedData.data()), size).AsMap();

    """
        # data.dngdRVLn = root["dngdRVLn"].AsString().str();
        if self.tkey == "string":
            for key in self.key_value_pair.keys():
                header_content += f"        data.{key} = root[\"{key}\"].AsString().str();\n"
        elif self.tkey == "int32_t":
            for key in self.key_value_pair.keys():
                header_content += f"        data.{key} = root[\"{key}\"].AsInt32();\n"
        elif self.tkey == "double":
            for key in self.key_value_pair.keys():
                header_content += f"        data.{key} = root[\"{key}\"].AsDouble();\n"


        header_content += """    }
    }
    """
        return header_content