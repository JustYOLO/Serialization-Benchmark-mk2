import string
import random

CHARSET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

class msgpack_gen:
    msgpack_cc = """#include "../data_generator.h"
// this may only used by msgPack

void DataGenerator::fillString(testData& data, const std::vector<std::string> &values) {
    
"""
    def __init__(self, nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, key_value_pair, testSize) -> None:
        self.nkey = nkey
        self.tkey = tkey
        self.skeyMin = skeyMin
        self.skeyMax = skeyMax
        self.svalMin = svalMin
        self.svalMax = svalMax
        self.key_value_pair = key_value_pair
        self.testSize = testSize

    def gen_header(self) -> str:
        struct_content = f"""#pragma once
#include <cstdint>
#include <string>
#include <msgpack.hpp>
// Automatically generated struct by generate_struct.py
// Number of keys: {self.nkey}
// Key type: {self.tkey}
// Key size bound: [{self.skeyMin}, {self.skeyMax}]
// Value size bound: [{self.svalMin}, {self.svalMax}]

struct testData {{
""" 
        if(self.tkey != "string"): 
            for i in range(self.nkey):
                while True:
                    tmp = ''.join(random.SystemRandom().choice(string.ascii_lowercase) for _ in range(random.randint(self.skeyMin, self.skeyMax)))
                    if tmp not in self.key_value_pair.keys():
                        struct_content += f"    {self.tkey} {tmp};\n" # TODO: set key name based on zipfian
                        self.key_value_pair[tmp] = 1 # value is used only in string type
                        break
        else: # in case of string
            for i in range(self.nkey): 
                while True:
                    tmp = ''.join(random.SystemRandom().choice(string.ascii_lowercase) for _ in range(random.randint(self.skeyMin, self.skeyMax)))
                    if tmp not in self.key_value_pair.keys():
                        self.key_value_pair[tmp] = []
                        struct_content += f"    std::string {tmp};\n"
                        for _ in range(self.testSize):
                            self.key_value_pair[tmp].append(''.join(random.SystemRandom().choice(CHARSET) for _ in range(random.randint(self.svalMin, self.svalMax))))
                        break

        
        struct_content += "    MSGPACK_DEFINE_MAP("
        for idx, name in enumerate(self.key_value_pair.keys()):
            if idx == len(self.key_value_pair.keys()) - 1:
                struct_content += name
            else:
                struct_content += name + ", "
        struct_content += ");\n"
        
        struct_content += "};\n\n"
        return struct_content

    def gen_cc(self) -> str:
        i = 0
        content = ""
        content += self.msgpack_cc
        if self.tkey == "string":
            for idx, name in enumerate(self.key_value_pair.keys()):
                content += f"    data.{name} = values[{idx}];\n"
        content += "}\n"
        return content

