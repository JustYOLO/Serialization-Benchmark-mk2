#include <nlohmann/json.hpp>
#include "benchmark_struct.h"
using jsonStruct = nlohmann::json;

namespace json {
    size_t Serialize(const testData& data, std::vector<char> &serializedData) {
    jsonStruct j = {
        // {"{key}", data.{key}},
        {"zvtecooq", data.zvtecooq},
        {"yhavzzus", data.yhavzzus},
        {"bdarcopv", data.bdarcopv},
        {"zyxhbtad", data.zyxhbtad},
        {"bifsqzpy", data.bifsqzpy},
        {"wpeblhba", data.wpeblhba},
        {"eqohxbbj", data.eqohxbbj},
        {"rgmckfxb", data.rgmckfxb},
        };
            std::string buf =  j.dump(4);
            serializedData.resize(buf.size());
            std::memcpy(serializedData.data(), buf.c_str(), buf.size());
            return buf.size();
        }

        void Deserialize(testData& data, std::vector<char> &serializedData, const size_t size) {
            jsonStruct j = jsonStruct::parse(serializedData);

            // data.{key} = j["{key}"];
            data.zvtecooq = j["zvtecooq"];
        data.yhavzzus = j["yhavzzus"];
        data.bdarcopv = j["bdarcopv"];
        data.zyxhbtad = j["zyxhbtad"];
        data.bifsqzpy = j["bifsqzpy"];
        data.wpeblhba = j["wpeblhba"];
        data.eqohxbbj = j["eqohxbbj"];
        data.rgmckfxb = j["rgmckfxb"];
    }
    }
    