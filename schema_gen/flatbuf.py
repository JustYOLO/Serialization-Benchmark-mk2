class flatbuf_gen:
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
        struct_content = """table flatData {
"""
        if self.tkey == "string":
            for key in self.key_value_pair.keys():
                struct_content += f"    {key}: string;\n"
        elif self.tkey == "int32_t":
            for key in self.key_value_pair.keys():
                struct_content += f"    {key}: int;\n"
        elif self.tkey == "double":
            for key in self.key_value_pair.keys():
                struct_content += f"    {key}: double;\n"
        struct_content += """}
root_type flatData;
"""
        return struct_content

    def gen_header(self) -> str:
        func_content = """#include <flatbuffers/flatbuffers.h>
#include <vector>
#include "benchmark_struct.h"
#include "../schema/struct_generated.h"

namespace flat {
    size_t Serialize(const testData& data, std::vector<char> &serializedData) {
        flatbuffers::FlatBufferBuilder builder;
"""
        if self.tkey == "string":
            func_content += f"        std::vector<flatbuffers::Offset<flatbuffers::String>> keys;\n"
            for key in self.key_value_pair.keys():
                func_content += f"        keys.push_back(builder.CreateString(data.{key}));\n"
            func_content += f"        auto result = CreateflatData(builder, "
            for idx, key in enumerate(self.key_value_pair.keys()):
                if idx == len(self.key_value_pair.keys()) - 1:
                    func_content += f"keys[{idx}]"
                else:
                    func_content += f"keys[{idx}], "
            func_content += f");"
        else:
            func_content += f"        auto result = CreateflatData(builder, "
            for idx, key in enumerate(self.key_value_pair.keys()):
                if idx == len(self.key_value_pair.keys()) - 1:
                    func_content += f"data.{key}"
                else:
                    func_content += f"data.{key}, "
            func_content += f");"
        func_content += """
        builder.Finish(result);
        serializedData.resize(builder.GetSize());
        std::memcpy(serializedData.data(), builder.GetBufferPointer(), builder.GetSize());
        return builder.GetSize();
    }
    
    void Deserialize(testData& data, std::vector<char> &serializedData, const size_t size) {
        auto flatData = GetflatData(serializedData.data());
"""
        if self.tkey == "string":
            for key in self.key_value_pair.keys():
                func_content += f"        data.{key} = flatData->{key}()->str();\n"
        else:
            for key in self.key_value_pair.keys():
                func_content += f"        data.{key} = flatData->{key}();\n"
        func_content += """        // data.{keys} = flatData->{keys}()->c_str();
    }
}
"""
        return func_content
