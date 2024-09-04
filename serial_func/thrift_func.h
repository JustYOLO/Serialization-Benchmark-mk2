#include <thrift/protocol/TBinaryProtocol.h>
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
        tStruct.struct = data.struct;
        tStruct.mjogvdtj = data.mjogvdtj;
        tStruct.int = data.int;
        tStruct.float = data.float;
        tStruct.string = data.string;


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
        data.struct = tStruct.struct;
        data.mjogvdtj = tStruct.mjogvdtj;
        data.int = tStruct.int;
        data.float = tStruct.float;
        data.string = tStruct.string;
    }
    }
    