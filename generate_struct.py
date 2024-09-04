'''
    Improvements:
        1. error handling
        2. tkey type checking
'''

import random
# import string
# import numpy
# import math
import schema_gen.msgpack as msgpack
import schema_gen.protobuf as protobuf
import schema_gen.flexbuf as flexbuf
import schema_gen.thrift as thrift
import schema_gen.flatbuf as flatbuf
import schema_gen.json as json

CHARSET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
COMBINED_TYPES = ["int", "float", "string"]

key_value_pair = {} # contains key-value pair
# in combined, the key is for types (e.g. int, string, n_int: means nested int), and value is for the key name

def generate_values_file(testSize, svalMin, svalMax, tkey, nkey, arrLen):
    with open("values.txt", "w") as f:
        if tkey != "combined":
            for i in range(testSize):
                for key in key_value_pair.keys():
                    f.write(key_value_pair[key][i] + ", ")
                f.write("\n")
        elif tkey == "combined":
            for i in range(testSize):
                for _ in range(nkey + arrLen * nkey):
                    f.write(''.join(random.SystemRandom().choice(CHARSET) for _ in range(random.randint(svalMin, svalMax))) + ", ")
                f.write("\n")

with open("config.txt", "r") as f:
    nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, arrLen, testSize = f.readline().split(", ")
nkey, skeyMin, skeyMax, svalMin, svalMax, testSize, arrLen = map(int, (nkey, skeyMin, skeyMax, svalMin, svalMax, testSize, arrLen))

msg_gen = msgpack.msgpack_gen(nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, arrLen, key_value_pair, testSize, COMBINED_TYPES)
pb_gen = protobuf.protobuf_gen(nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, arrLen, key_value_pair, testSize, COMBINED_TYPES)
flexbuf_gen = flexbuf.flexbuf_gen(nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, arrLen, key_value_pair, testSize, COMBINED_TYPES)
th_gen = thrift.thrift_gen(nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, arrLen, key_value_pair, testSize, COMBINED_TYPES)
flatbuf_gen = flatbuf.flatbuf_gen(nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, arrLen, key_value_pair, testSize, COMBINED_TYPES)
json_gen = json.json_gen(nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, arrLen, key_value_pair, testSize, COMBINED_TYPES)

# TODO: consider moving these below 2 files into root directory
with open("./serial_func/benchmark_struct.h", "w") as f: 
    f.write(msg_gen.gen_header())
with open("./serial_func/data_generator_string.cc", "w") as f:
    f.write(msg_gen.gen_cc())

with open("./schema/ProtoData.proto", "w") as f:
    f.write(pb_gen.gen_schema())
with open("./serial_func/protobuf_func.h", "w") as f:
    f.write(pb_gen.gen_header())

with open("./serial_func/flexbuffers_func.h", "w") as f:
    f.write(flexbuf_gen.gen_header())

with open("./schema/struct.thrift", "w") as f:
    f.write(th_gen.gen_schema())
with open("./serial_func/thrift_func.h", "w") as f:
    f.write(th_gen.gen_header())

with open("./schema/struct.fbs", "w") as f:
    f.write(flatbuf_gen.gen_schema())
with open("./serial_func/flatbuffers_func.h", "w") as f:
    f.write(flatbuf_gen.gen_header())

with open("./serial_func/json_func.h", "w") as f:
    f.write(json_gen.gen_header())

if(tkey == "string" or tkey == "combined"):
    generate_values_file(testSize, svalMin, svalMax, tkey, nkey, arrLen)

print("structures have been generated.")