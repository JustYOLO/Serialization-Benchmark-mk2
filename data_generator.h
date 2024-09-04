#include "./serial_func/benchmark_struct.h"
#include <random>
#include <type_traits>

class DataGenerator {
public:
    DataGenerator(unsigned seed = std::random_device{}());

    void fillStruct(testData& data, const std::string& type, const std::vector<std::string> &values);

private:
    std::mt19937 gen;

    template<typename T>
    T generateRandomValue();

    void fillInt32(testData& data);
    void fillDouble(testData& data);
    // void fillString(testData& data, size_t nkeys, size_t svalMin, size_t svalMax, const std::vector<std::string> &values);
    void fillString(testData& data, const std::vector<std::string> &values);
    void fillCombined(testData& data, const std::vector<std::string> &values);
};

// Template specializations for different types
template<>
int32_t DataGenerator::generateRandomValue<int32_t>();

template<>
double DataGenerator::generateRandomValue<double>();

template<>
float DataGenerator::DataGenerator::generateRandomValue<float>();