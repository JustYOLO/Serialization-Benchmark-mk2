#include "data_generator.h"
#include <algorithm>
#include <cstring>
#include <stdexcept>
#include <cstdlib>

DataGenerator::DataGenerator(unsigned seed) : gen(seed) {}

// void DataGenerator::fillStruct(testData& data, size_t nkeys, size_t svalMin, size_t svalMax, const std::string& type, const std::vector<std::string> &values) {
void DataGenerator::fillStruct(testData& data, const std::string& type, const std::vector<std::string> &values) {
    if (type == "int32_t") {
        fillInt32(data);
    } else if (type == "double") {
        fillDouble(data);
    } else if (type == "string") {
        fillString(data, values);
    } else if(type == "combined") {
        fillCombined(data, values);
    } else {
        throw std::runtime_error("Unsupported type");
    }
}

void DataGenerator::fillInt32(testData& data) {
    int32_t* ptr = reinterpret_cast<int32_t*>(&data); // Is it ok to use reinterpret_cast? Is there any better method?
    size_t num_members = sizeof(testData) / sizeof(int32_t);
    for (size_t i = 0; i < num_members; ++i) {
        ptr[i] = generateRandomValue<int32_t>();
    }
}

void DataGenerator::fillDouble(testData& data) {
    double* ptr = reinterpret_cast<double*>(&data);
    size_t num_members = sizeof(testData) / sizeof(double);
    for (size_t i = 0; i < num_members; ++i) {
        ptr[i] = generateRandomValue<double>();
    }
}

// template<>
// int32_t DataGenerator::generateRandomValue<int32_t>() {
//     return std::uniform_int_distribution<int32_t>{}(gen);
// }

template<> 
int DataGenerator::generateRandomValue<int>() {
    return std::uniform_int_distribution<int>{}(gen);
} // TODO: int vs int32_t ?

template<>
double DataGenerator::generateRandomValue<double>() {
    return std::uniform_real_distribution<double>{}(gen);
}

template<>
float DataGenerator::generateRandomValue<float>() {
    return std::uniform_real_distribution<float>{}(gen);
}