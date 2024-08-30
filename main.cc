#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <benchmark/benchmark.h>
#include <functional>
#include "data_generator.h"
#include "./serial_func/benchmark_struct.h"
#include "./serial_func/serializers.h"
#include "./serial_func/benchmark_func.h"

enum funcEnum {
    // first six is serial
    jsonSerial,
    flatbufSerial,
    msgpackSerial,
    flexbufSerial,
    protobufSerial,
    thriftSerial,
    serialLast,
    // last six is deserial
    jsonDeserial,
    flatbufDeserial,
    msgpackDeserial,
    flexbufDeserial,
    protobufDeserial,
    thriftDeserial,
    deserialLast,
};

void getTokens(std::vector<std::string> &tokens) {
    std::ifstream config_file("config.txt");
    std::string line;
    std::getline(config_file, line);
    std::replace(line.begin(), line.end(), ',', ' ');
    std::istringstream iss(line);
    std::string s;
    while (iss >> s) {
        tokens.push_back(s);
    }

    if (tokens.size() < 6) {
        std::cerr << "Error: Not enough parameters in config file" << std::endl;
        exit(1);
    }
}

void getValues(std::vector<std::string> *values, size_t testSize) {
    std::ifstream config_file("values.txt");
    std::string line;
    for (size_t i = 0; i < testSize; ++i) {
        std::getline(config_file, line);
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream iss(line);
        std::string s;
        while (iss >> s) {
            values[i].push_back(s);
        }
    }
}

class CustomReporter : public benchmark::BenchmarkReporter {
public:
    CustomReporter(std::string& settings) 
        : consoleReporter() {
        latencyFile[jsonSerial].open("results/" + settings + "-json-serial-latency.txt");
        sizeFile[jsonSerial].open("results/" + settings + "-json-size.txt");
        latencyFile[jsonDeserial].open("results/" + settings + "-json-deserial-latency.txt");

        latencyFile[flatbufSerial].open("results/" + settings + "-flatbuf-serial-latency.txt");
        sizeFile[flatbufSerial].open("results/" + settings + "-flatbuf-size.txt");
        latencyFile[flatbufDeserial].open("results/" + settings + "-flatbuf-deserial-latency.txt");

        latencyFile[msgpackSerial].open("results/" + settings + "-msgpack-serial-latency.txt");
        sizeFile[msgpackSerial].open("results/" + settings + "-msgpack-size.txt");
        latencyFile[msgpackDeserial].open("results/" + settings + "-msgpack-deserial-latency.txt");

        latencyFile[flexbufSerial].open("results/" + settings + "-flexbuf-serial-latency.txt");
        sizeFile[flexbufSerial].open("results/" + settings + "-flexbuf-size.txt");
        latencyFile[flexbufDeserial].open("results/" + settings + "-flexbuf-deserial-latency.txt");

        latencyFile[protobufSerial].open("results/" + settings + "-protobuf-serial-latency.txt");
        sizeFile[protobufSerial].open("results/" + settings + "-protobuf-size.txt");
        latencyFile[protobufDeserial].open("results/" + settings + "-protobuf-deserial-latency.txt");

        latencyFile[thriftSerial].open("results/" + settings + "-thrift-serial-latency.txt");
        sizeFile[thriftSerial].open("results/" + settings + "-thrift-size.txt");
        latencyFile[thriftDeserial].open("results/" + settings + "-thrift-deserial-latency.txt");
        
    }

    bool ReportContext(const Context& context) override {
        consoleReporter.ReportContext(context);
        return true;
    }

    void ReportRuns(const std::vector<Run>& report) override {
        for (const auto& run : report) {
            double time_ns = (run.real_accumulated_time * 1e9) / run.iterations;
            // run.benchmark_name();
            latencyBuf[whichFunc(run.benchmark_name())] += std::to_string(time_ns) + " ns\n";
            if (!run.report_label.empty()) {
                sizeBuf[whichFunc(run.benchmark_name())] += run.report_label + "\n";
            }
        }
        consoleReporter.ReportRuns(report);
    }

    void Finalize() override {
        // serializing funcions
        for (int i = jsonSerial; i != serialLast; i++ ) {
            funcEnum func = static_cast<funcEnum>(i);
            latencyFile[func] << latencyBuf[func];
            latencyFile[func].close();
            sizeFile[func] << sizeBuf[func];
            sizeFile[func].close();
        }
        // deserializing functions
        for (int i = jsonDeserial; i != deserialLast; i++) {
            funcEnum func = static_cast<funcEnum>(i);
            latencyFile[func] << latencyBuf[func];
            latencyFile[func].close();
        }
        consoleReporter.Finalize();
    }

    funcEnum whichFunc(std::string funcName) {
        if(funcName.find("MsgPackSerialization") != std::string::npos) {
            return funcEnum::msgpackSerial;
        } else if(funcName.find("MsgPackDeserialization") != std::string::npos) {
            return funcEnum::msgpackDeserial;
        } 
        else if(funcName.find("ProtoBufSerialization") != std::string::npos) {
            return funcEnum::protobufSerial;
        } else if(funcName.find("ProtoBufDeserialization") != std::string::npos) {
            return funcEnum::protobufDeserial;
        } 
        else if(funcName.find("FlexBufSerialization") != std::string::npos) {
            return funcEnum::flexbufSerial;
        } else if(funcName.find("FlexBufDeserialization") != std::string::npos) {
            return funcEnum::flexbufDeserial;
        } 
        else if(funcName.find("ThriftSerialization") != std::string::npos) {
            return funcEnum::thriftSerial;
        } else if(funcName.find("ThriftDeserialization") != std::string::npos) {
            return funcEnum::thriftDeserial;
        } 
        else if(funcName.find("FlatBufSerialization") != std::string::npos) {
            return funcEnum::flatbufSerial;
        } else if(funcName.find("FlatBufDeserialization") != std::string::npos) {
            return funcEnum::flatbufDeserial;
        }
        else if(funcName.find("JsonSerialization") != std::string::npos) {
            return funcEnum::jsonSerial;
        } else if(funcName.find("JsonDeserialization") != std::string::npos) {
            return funcEnum::jsonDeserial;
        }
        else {
            std::cout << "something is wrong!!!" << std::endl;
            exit(-1);
        }
    }

private:
    std::map<funcEnum, std::string> latencyBuf; 
    std::map<funcEnum, std::string> sizeBuf;
    std::map<funcEnum, std::ofstream> latencyFile;
    std::map<funcEnum, std::ofstream> sizeFile;
    benchmark::ConsoleReporter consoleReporter;
};


int main(int argc, char** argv) {
    std::vector<std::string> tokens;    
    getTokens(tokens);

    size_t nkeys = std::stoi(tokens[0]);
    size_t skeyMin = std::stoi(tokens[2]);
    size_t skeyMax = std::stoi(tokens[3]);
    size_t svalMin = std::stoi(tokens[4]);
    size_t svalMax = std::stoi(tokens[5]);
    size_t testSize = std::stoi(tokens[6]);
    std::string type = tokens[1];

    std::vector<std::string> values[testSize];
    if (type == "string") {
        getValues(values, testSize);
    }

    benchmark::Initialize(&argc, argv);
    DataGenerator generator;
    std::vector<std::vector<std::vector<char>>> serializedData(testSize, std::vector<std::vector<char>>(6));
    std::vector<std::vector<size_t>> sizes(testSize, std::vector<size_t>(6));


    std::vector<testData> testDataVector(testSize);
    for (size_t i = 0; i < testSize; ++i) {
        generator.fillStruct(testDataVector[i], type, values[i]);
        std::string index_str = std::to_string(i);

        // Register serialization benchmarks
        benchmark::RegisterBenchmark(("BM_JsonSerialization_" + index_str).c_str(), BM_JsonSerialization, testDataVector[i], std::ref(serializedData[i][0]), std::ref(sizes[i][0]));
        benchmark::RegisterBenchmark(("BM_FlatBufSerialization_" + index_str).c_str(), BM_FlatBufSerialization, testDataVector[i], std::ref(serializedData[i][1]), std::ref(sizes[i][1]));
        benchmark::RegisterBenchmark(("BM_MsgPackSerialization_" + index_str).c_str(), BM_MsgPackSerialization, testDataVector[i], std::ref(serializedData[i][2]), std::ref(sizes[i][2]));
        benchmark::RegisterBenchmark(("BM_FlexBufSerialization_" + index_str).c_str(), BM_FlexBufSerialization, testDataVector[i], std::ref(serializedData[i][3]), std::ref(sizes[i][3]));
        benchmark::RegisterBenchmark(("BM_ProtoBufSerialization_" + index_str).c_str(), BM_ProtoBufSerialization, testDataVector[i], std::ref(serializedData[i][4]), std::ref(sizes[i][4]));
        benchmark::RegisterBenchmark(("BM_ThriftSerialization_" + index_str).c_str(), BM_ThriftSerialization, testDataVector[i], std::ref(serializedData[i][5]), std::ref(sizes[i][5]));

        // Register deserialization benchmarks
        benchmark::RegisterBenchmark(("BM_JsonDeserialization_" + index_str).c_str(), BM_JsonDeserialization, std::ref(serializedData[i][0]), std::ref(sizes[i][0]));
        benchmark::RegisterBenchmark(("BM_FlatBufDeserialization_" + index_str).c_str(), BM_FlatBufDeserialization, std::ref(serializedData[i][1]), std::ref(sizes[i][1]));
        benchmark::RegisterBenchmark(("BM_MsgPackDeserialization_" + index_str).c_str(), BM_MsgPackDeserialization, std::ref(serializedData[i][2]), std::ref(sizes[i][2]));
        benchmark::RegisterBenchmark(("BM_FlexBufDeserialization_" + index_str).c_str(), BM_FlexBufDeserialization, std::ref(serializedData[i][3]), std::ref(sizes[i][3]));
        benchmark::RegisterBenchmark(("BM_ProtoBufDeserialization_" + index_str).c_str(), BM_ProtoBufDeserialization, std::ref(serializedData[i][4]), std::ref(sizes[i][4]));
        benchmark::RegisterBenchmark(("BM_ThriftDeserialization_" + index_str).c_str(), BM_ThriftDeserialization, std::ref(serializedData[i][5]), std::ref(sizes[i][5]));
    }

    std::string fileHeader = std::to_string(nkeys) + "-" + type + "-" + std::to_string(skeyMin) + "-" + std::to_string(skeyMax) + "-" + std::to_string(svalMin) + "-" + std::to_string(svalMax) + "-" + std::to_string(testSize);
    CustomReporter reporter(fileHeader);

    auto start_time = std::chrono::high_resolution_clock::now();
    
    benchmark::RunSpecifiedBenchmarks(&reporter);

    benchmark::Shutdown();

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "Total elapsed time: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
