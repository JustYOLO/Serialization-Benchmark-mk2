#include "../data_generator.h"
// this may only used by msgPack

void DataGenerator::fillString(testData& data, const std::vector<std::string> &values) {
}
void DataGenerator::fillCombined(testData& data, const std::vector<std::string> &values) {
    for(int i = 0; i < 3; i++) {
        data.jmihzbsn[i].raxmltsa = generateRandomValue<int>();
        data.jmihzbsn[i].zwdygjzg = values[(i + 1) * 2 + 0];
    }
}
