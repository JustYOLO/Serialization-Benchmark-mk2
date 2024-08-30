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
        tStruct.zvtecooq = data.zvtecooq;
        tStruct.yhavzzus = data.yhavzzus;
        tStruct.bdarcopv = data.bdarcopv;
        tStruct.zyxhbtad = data.zyxhbtad;
        tStruct.bifsqzpy = data.bifsqzpy;
        tStruct.wpeblhba = data.wpeblhba;
        tStruct.eqohxbbj = data.eqohxbbj;
        tStruct.rgmckfxb = data.rgmckfxb;


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
            data.zvtecooq = tStruct.zvtecooq;
        data.yhavzzus = tStruct.yhavzzus;
        data.bdarcopv = tStruct.bdarcopv;
        data.zyxhbtad = tStruct.zyxhbtad;
        data.bifsqzpy = tStruct.bifsqzpy;
        data.wpeblhba = tStruct.wpeblhba;
        data.eqohxbbj = tStruct.eqohxbbj;
        data.rgmckfxb = tStruct.rgmckfxb;
    }
    }
    