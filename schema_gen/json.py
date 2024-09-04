class json_gen:
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
        self.COMBINED_TYPES = combined_types

    def gen_header(self) -> str:
        func_content = """#include <nlohmann/json.hpp>
#include "benchmark_struct.h"
using jsonStruct = nlohmann::json;

namespace json {
    size_t Serialize(const testData& data, std::vector<char> &serializedData) {
        jsonStruct j = {
            // {"{key}", data.{key}},
"""
        for key in self.key_value_pair.keys():
            func_content += f"            {{\"{key}\", data.{key}}},\n"
        func_content += """        };
        std::string buf =  j.dump(4);
        serializedData.resize(buf.size());
        std::memcpy(serializedData.data(), buf.c_str(), buf.size());
        return buf.size();
    }

    void Deserialize(testData& data, std::vector<char> &serializedData, const size_t size) {
        jsonStruct j = jsonStruct::parse(serializedData);

        // data.{key} = j["{key}"];
"""
        for key in self.key_value_pair.keys():
            func_content += f"        data.{key} = j[\"{key}\"];\n"
        func_content += """    }
}
"""
        return func_content
