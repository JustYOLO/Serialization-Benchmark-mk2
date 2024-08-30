class thrift_gen:
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
        thrift_content = """struct TStruct {
"""
        if self.tkey == "string":
            for idx, key in enumerate(self.key_value_pair.keys()):
                thrift_content += f" {idx+1}: string {key},\n"
        elif self.tkey == "int32_t":
            for idx, key in enumerate(self.key_value_pair.keys()):
                thrift_content += f" {idx+1}: i32 {key},\n"
        elif self.tkey == "double":
            for idx, key in enumerate(self.key_value_pair.keys()):
                thrift_content += f" {idx+1}: double {key},\n"
        thrift_content += "}\n"

        return thrift_content

    def gen_header(self) -> str:
        struct_content = """#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TBufferTransports.h>
#include <vector>
#include "../gen-cpp/struct_types.h"
#include "benchmark_struct.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

namespace thrift {
    size_t Serialize(const testData& data, std::vector<char> &serializedData) {
        TStruct tStruct;
"""
        for key in self.key_value_pair.keys():
            struct_content += f"        tStruct.{key} = data.{key};\n"
        struct_content += """

        std::shared_ptr<TMemoryBuffer> buffer(new TMemoryBuffer());
        std::shared_ptr<TBinaryProtocol> protocol(new TBinaryProtocol(buffer));

        tStruct.write(protocol.get());

        uint8_t* buf;
        uint32_t size;
        buffer->getBuffer(&buf, &size);

        serializedData.resize(size);
        std::memcpy(serializedData.data(), buf, size);

        return size;
    }

    void Deserialize(testData& data, std::vector<char> &serializedData, const size_t size) {
        std::shared_ptr<TMemoryBuffer> bufferIn(new TMemoryBuffer());
        bufferIn->write((uint8_t*)(serializedData.data()), size);
        std::shared_ptr<TBinaryProtocol> protocolIn(new TBinaryProtocol(bufferIn));

        TStruct tStruct;
        tStruct.read(protocolIn.get());
    """
        for key in self.key_value_pair.keys():
            struct_content += f"        data.{key} = tStruct.{key};\n"
        struct_content += """    }
    }
    """
        return struct_content