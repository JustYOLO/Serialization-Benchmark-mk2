#pragma once
#include <cstdint>
#include <string>
#include <msgpack.hpp>
// Automatically generated struct by generate_struct.py
// Number of keys: 2
// Key type: combined
// Key size bound: [8, 8]
// Value size bound: [16, 16]
// Struct array length: 3

struct testData {
    int wfxtqnoc;
    int xzepbayf;
    float wllldavf;
    float todnlesm;
    std::string ahpotwhv;
    std::string jnxqcwxf;
    struct nested {
        int tkuuzxpp;
        int raxmltsa;
        float bfabwiyj;
        float zlvlpass;
        std::string zwdygjzg;
        std::string hlirxqvq;
        MSGPACK_DEFINE_MAP(tkuuzxpp, raxmltsa, bfabwiyj, zlvlpass, zwdygjzg, hlirxqvq);
    } jmihzbsn[3];
    MSGPACK_DEFINE_MAP(wfxtqnoc, xzepbayf, wllldavf, todnlesm, ahpotwhv, jnxqcwxf, jmihzbsn);
};

