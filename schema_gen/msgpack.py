import string
import random

CHARSET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
keyName = [] # for checking duplicated key name

class msgpack_gen:
    msgpack_cc = """#include "../data_generator.h"
// this may only used by msgPack

"""
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
    
    def gen_rand_name(self) -> str:
        tmp = ''.join(random.SystemRandom().choice(string.ascii_lowercase) for _ in range(random.randint(self.skeyMin, self.skeyMax)))
        return tmp

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
// Struct array length: {self.arrLen}

""" 
        if(self.tkey == "combined"):
            tmp = self.gen_rand_name()
            self.key_value_pair['struct'] = tmp
            self.key_value_pair[tmp] = {}
            nested = tmp # generate nested struct name

            for type in self.COMBINED_TYPES:
                self.key_value_pair[type] = []

            struct_content += "struct testData {\n"
            for i in range(len(self.COMBINED_TYPES)):
                num = 0
                while num < self.nkey:
                    tmp = self.gen_rand_name()
                    if tmp not in keyName:
                        if self.COMBINED_TYPES[i] != "string":
                            struct_content += f"    {self.COMBINED_TYPES[i]} {tmp};\n"
                            self.key_value_pair[self.COMBINED_TYPES[i]].append(tmp)
                            keyName.append(tmp)
                            num += 1
                        else:
                            struct_content += f"    std::string {tmp};\n"
                            self.key_value_pair['string'].append(tmp)
                            keyName.append(tmp)
                            num += 1
            struct_content += "    struct nested {\n"
            self.key_value_pair[nested] = {}
            for type in self.COMBINED_TYPES:
                self.key_value_pair[nested][type] = []
            for i in range(len(self.COMBINED_TYPES)):
                num = 0
                while num < self.nkey:
                    tmp = self.gen_rand_name()
                    if tmp not in keyName:
                        if self.COMBINED_TYPES[i] != "string":
                            struct_content += f"        {self.COMBINED_TYPES[i]} {tmp};\n"
                            self.key_value_pair[nested][self.COMBINED_TYPES[i]].append(tmp)
                            num += 1
                        else:
                            struct_content += f"        std::string {tmp};\n"
                            self.key_value_pair[nested]['string'].append(tmp)
                            num += 1
            struct_content += "        MSGPACK_DEFINE_MAP("
            for type in self.COMBINED_TYPES:
                for key in self.key_value_pair[nested][type]:
                    struct_content += key + ", "
            struct_content = struct_content[:-2] # remove last comma
            struct_content += f");\n    }} {nested}[{self.arrLen}];\n"
        
        elif(self.tkey != "string"):
            struct_content += f"struct testData {{\n"
            for i in range(self.nkey):
                while True:
                    tmp = ''.join(random.SystemRandom().choice(string.ascii_lowercase) for _ in range(random.randint(self.skeyMin, self.skeyMax)))
                    if tmp not in self.key_value_pair.keys():
                        struct_content += f"    {self.tkey} {tmp};\n" # TODO: set key name based on zipfian
                        self.key_value_pair[tmp] = 1 # value is used only in string type
                        break

        else: # in case of string
            struct_content += f"struct testData {{\n"
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
        if self.tkey != "combined":
            for idx, name in enumerate(self.key_value_pair.keys()):
                if idx == len(self.key_value_pair.keys()) - 1:
                    struct_content += name
                else:
                    struct_content += name + ", "
        else: # in case of combined
            for type in self.COMBINED_TYPES:
                for idx, name in enumerate(self.key_value_pair[type]):
                        struct_content += name + ", "
        struct_content += nested
        struct_content += ");\n"

        struct_content += "};\n\n"
        return struct_content

    def gen_cc(self) -> str:
        content = self.msgpack_cc
        content += "void DataGenerator::fillString(testData& data, const std::vector<std::string> &values) {\n"
        if self.tkey == "string":
            for idx, name in enumerate(self.key_value_pair.keys()):
                content += f"    data.{name} = values[{idx}];\n"
            content += "void DataGenerator::fillCombined(testData& data, const std::vector<std::string> &values) {\n}\n"
        if self.tkey == "combined":
            nested = self.key_value_pair['struct']
            content += "}\n"
            content += "void DataGenerator::fillCombined(testData& data, const std::vector<std::string> &values) {\n"
            # first, fill the outer struct's element
            for type in self.COMBINED_TYPES:
                if type != "string":
                    for key in self.key_value_pair[type]:
                        content += f"    data.{key} = generateRandomValue<{type}>();\n"
                else:
                    for idx, key in enumerate(self.key_value_pair[type]):
                        content += f"    data.{key} = values[{idx}];\n"
            # then, fill the nested struct's element
            content += f"    for(int i = 0; i < {self.arrLen}; i++) {{\n"
            for type in self.COMBINED_TYPES:
                if type != "string":
                    for key in self.key_value_pair[nested][type]:
                        content += f"        data.{nested}[i].{key} = generateRandomValue<{type}>();\n"
                else: # in case of string
                    for idx, key in enumerate(self.key_value_pair[nested][type]):
                        content += f"        data.{nested}[i].{key} = values[(i + 1) * {self.nkey} + {idx}];\n"

            content += "    }\n"

        content += "}\n"
        return content

