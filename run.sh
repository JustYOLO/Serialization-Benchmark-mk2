#!/bin/sh
python3 generate_struct.py
cd schema
protoc --cpp_out=./ ProtoData.proto # for making protobuf struct
cd ..
thrift --gen cpp ./schema/struct.thrift # for making thrift struct
flatc -o ./schema --cpp ./schema/struct.fbs # for making flatbuffers struct

make clean
make

./benchmark_test
