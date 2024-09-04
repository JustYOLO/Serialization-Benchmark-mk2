class flatbuf_gen:
    def __init__(self, nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, arrLen, key_value_pair, testSize, combined_types) -> None:
        self.nkey = nkey
        self.tkey = tkey
        self.skeyMin = skeyMin
        self.skeyMax = skeyMax
        self.svalMin = svalMin
        self.svalMax = svalMax
        self.key_value_pair = key_value_pair
        self.testSize = testSize
        self.arrLen = arrLen
        self.match(combined_types)
    
    def match(self, combined_types):
        '''
        match each type with flatbuffer types
        '''
        self.COMBINED_TYPES = {}
        for type in combined_types:
            if type == "int":
                self.COMBINED_TYPES["int"] = "int32"
            elif type == "float":
                self.COMBINED_TYPES["float"] = "float"
            elif type == "string":
                self.COMBINED_TYPES["string"] = "string"


    def gen_schema(self) -> str:
        struct_content = ""
        if self.tkey != "combined": # in case of not combined types
            struct_content += """table flatData {
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
        
        elif self.tkey == "combined": # in case of combined types
            nested = self.key_value_pair['struct']
            struct_content += """table fNested {
"""
            for type in self.COMBINED_TYPES.keys():
                for key in self.key_value_pair[nested][type]:
                    struct_content += f"    {key}: {self.COMBINED_TYPES[type]};\n"

            struct_content += """}\n\ntable flatData {\n"""

            for type in self.COMBINED_TYPES.keys():
                for key in self.key_value_pair[type]:
                    struct_content += f"    {key}: {self.COMBINED_TYPES[type]};\n"

            struct_content += f"    {nested}: [fNested];\n"
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
        if self.tkey == "combined":
            nested = self.key_value_pair['struct']
            func_content += f"        std::vector<flatbuffers::Offset<fNested>> nested;\n"
            func_content += f"        for (int i = 0; i < {self.arrLen}; i++) {{\n"
            func_content += "            auto nestedData = CreatefNested(builder, "
            for type in self.COMBINED_TYPES.keys():
                if type != "string":
                    for key in self.key_value_pair[nested][type]:
                        func_content += f"data.{nested}[i].{key}, "
                else: # in case of string
                    for key in self.key_value_pair[nested][type]:
                        func_content += f"builder.CreateString(data.{nested}[i].{key}), "

            func_content = func_content[:-2] + ");\n            nested.push_back(nestedData);\n        }\n"
            func_content += "        auto result = CreateflatData(builder, "

            for type in self.COMBINED_TYPES.keys():
                if type != "string":
                    for key in self.key_value_pair[type]:
                        func_content += f"data.{key}, "
                else: # in case of string
                    for key in self.key_value_pair[type]:
                        func_content += f"builder.CreateString(data.{key}), "
            func_content += "builder.CreateVector(nested));\n"


        elif self.tkey == "string":
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
        if self.tkey == "combined":
            nested = self.key_value_pair['struct']
            for type in self.COMBINED_TYPES.keys(): # for each element in outer struct
                if type != "string":
                    for key in self.key_value_pair[type]:
                        func_content += f"        data.{key} = flatData->{key}();\n"
                else: # in case of string
                    for key in self.key_value_pair[type]:
                        func_content += f"        data.{key} = flatData->{key}()->c_str();\n"
            func_content += f"        for(int i = 0; i < {self.arrLen}; i++) {{\n"
            for type in self.COMBINED_TYPES.keys(): # for each element in nested struct
                if type != "string":
                    for key in self.key_value_pair[nested][type]:
                        func_content += f"            data.{nested}[i].{key} = flatData->{nested}()->Get(i)->{key}();\n"
                else: # in case of string
                    for key in self.key_value_pair[nested][type]:
                        func_content += f"            data.{nested}[i].{key} = flatData->{nested}()->Get(i)->{key}()->c_str();\n"
            func_content += "        }\n"
            
        elif self.tkey == "string":
            for key in self.key_value_pair.keys():
                func_content += f"        data.{key} = flatData->{key}()->str();\n"
        else:
            for key in self.key_value_pair.keys():
                func_content += f"        data.{key} = flatData->{key}();\n"
        func_content += """        // in case of strings:
        //  data.{keys} = flatData->{keys}()->c_str();
    }
}
"""
        return func_content
