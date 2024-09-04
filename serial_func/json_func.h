#include <nlohmann/json.hpp>
#include "benchmark_struct.h"
using jsonStruct = nlohmann::json;

namespace json {
    size_t Serialize(const testData& data, std::vector<char> &serializedData) {
        jsonStruct j = {
            // {"{key}", data.{key}},
            {"struct", data.struct},
            {"mjogvdtj", data.mjogvdtj},
            {"int", data.int},
            {"float", data.float},
            {"string", data.string},
        };
        std::string buf =  j.dump(4);
        serializedData.resize(buf.size());
        std::memcpy(serializedData.data(), buf.c_str(), buf.size());
        return buf.size();
    }

    void Deserialize(testData& data, std::vector<char> &serializedData, const size_t size) {
        jsonStruct j = jsonStruct::parse(serializedData);

        // data.{key} = j["{key}"];
        data.struct = j["struct"];
        data.mjogvdtj = j["mjogvdtj"];
        data.int = j["int"];
        data.float = j["float"];
        data.string = j["string"];
    }
}
