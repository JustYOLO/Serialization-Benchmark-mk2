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
    int lmontiqn;
    int gttsakbp;
    float sgruersi;
    float cbjiwmfv;
    std::string toiywwtb;
    std::string ojkinvvf;
    struct nested {
        int etiizwwn;
        int cbcfskih;
        float ldeucjga;
        float cgekyebx;
        std::string xgrdxjrt;
        std::string calizksb;
        MSGPACK_DEFINE_MAP(etiizwwn, cbcfskih, ldeucjga, cgekyebx, xgrdxjrt, calizksb);
    } mjogvdtj[3];
    MSGPACK_DEFINE_MAP(lmontiqn, gttsakbp, sgruersi, cbjiwmfv, toiywwtb, ojkinvvf, mjogvdtj);
};

