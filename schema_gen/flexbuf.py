class flexbuf_gen:
    def __init__(self, nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, arrLen, key_value_pair, testSize, combined_types, pValue, value_exists) -> None:
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
        self.pValue = pValue
        self.value_exists = value_exists

    def match(self, combined_types):
        '''
        match each type with flatbuffer types
        '''
        self.COMBINED_TYPES = {}
        for type in combined_types:
            if type == "int":
                self.COMBINED_TYPES["int"] = "Int"
            elif type == "float":
                self.COMBINED_TYPES["float"] = "Float"
            elif type == "string":
                self.COMBINED_TYPES["string"] = "String"

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
        elif self.tkey == "combined":
            nested = self.key_value_pair['struct']
            for type in self.COMBINED_TYPES.keys():
                for key in self.key_value_pair[type]:
                    if self.value_exists[key]:
                        header_content += f"            builder.{self.COMBINED_TYPES[type]}(\"{key}\", data.{key});\n"
            header_content += f"            builder.Vector(\"{nested}\", [&]() {{\n                for(int i = 0; i < {self.arrLen}; i++) {{\n                    builder.Map([&]() {{\n"
            for type in self.COMBINED_TYPES.keys():
                for key in self.key_value_pair[nested][type]:
                    if self.value_exists[key]:
                        header_content += f"                        builder.{self.COMBINED_TYPES[type]}(\"{key}\", data.{key});\n"
            header_content += """                    });\n                }\n            });\n"""

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
        elif self.tkey == "combined":
            nested = self.key_value_pair['struct']
            for type in self.COMBINED_TYPES.keys():
                for key in self.key_value_pair[type]:
                    if self.value_exists[key]:
                        if type != "string":
                            header_content += f"        data.{key} = root[\"{key}\"].As{self.COMBINED_TYPES[type]}();\n"
                        elif type == "int":
                            header_content += f"        data.{key} = root[\"{key}\"].As{self.COMBINED_TYPES[type]}32();\n"
                        else:
                            header_content += f"        data.{key} = root[\"{key}\"].As{self.COMBINED_TYPES[type]}().c_str();\n"
            header_content += f"        auto tmp = root[\"{nested}\"].AsVector();\n"
            header_content += f"        for(int i = 0; i < {self.arrLen}; i++) {{\n"
            for type in self.COMBINED_TYPES.keys():
                for key in self.key_value_pair[nested][type]:
                    if self.value_exists[key]:
                        if type != "string":
                            header_content += f"            data.{key} = tmp[i].AsMap()[\"{key}\"].As{self.COMBINED_TYPES[type]}();\n"
                        elif type == "int":
                            header_content += f"            data.{key} = tmp[i].AsMap()[\"{key}\"].As{self.COMBINED_TYPES[type]}32();\n"
                        else:
                            header_content += f"            data.{key} = tmp[i].AsMap()[\"{key}\"].As{self.COMBINED_TYPES[type]}().c_str();\n"
            header_content += """        }\n"""

        header_content += """    }
}
"""
        return header_content