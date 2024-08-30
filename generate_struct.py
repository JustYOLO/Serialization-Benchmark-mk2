'''
    Improvements:
        1. error handling
        2. tkey type checking
'''

# import random
# import string
# import numpy
# import math
import schema_gen.msgpack as msgpack
import schema_gen.protobuf as protobuf
import schema_gen.flexbuf as flexbuf
import schema_gen.thrift as thrift
import schema_gen.flatbuf as flatbuf
import schema_gen.json as json

key_value_pair = {} # have key-value pair

def generate_values_file(testSize):
    with open("values.txt", "w") as f:
        for i in range(testSize):
            for key in key_value_pair.keys():
                f.write(key_value_pair[key][i] + ", ")
            f.write("\n")

with open("config.txt", "r") as f:
    nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, testSize = f.readline().split(", ")
nkey, skeyMin, skeyMax, svalMin, svalMax, testSize = map(int, (nkey, skeyMin, skeyMax, svalMin, svalMax, testSize))

msg_gen = msgpack.msgpack_gen(nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, key_value_pair, testSize)
pb_gen = protobuf.protobuf_gen(nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, key_value_pair, testSize)
flexbuf_gen = flexbuf.flexbuf_gen(nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, key_value_pair, testSize)
th_gen = thrift.thrift_gen(nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, key_value_pair, testSize)
flatbuf_gen = flatbuf.flatbuf_gen(nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, key_value_pair, testSize)
json_gen = json.json_gen(nkey, tkey, skeyMin, skeyMax, svalMin, svalMax, key_value_pair, testSize)

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

if(tkey == "string"):
    generate_values_file(testSize)

print("structures have been generated.")