#include "../data_generator.h"
// this may only used by msgPack

void DataGenerator::fillString(testData& data, const std::vector<std::string> &values) {
}
void DataGenerator::fillCombined(testData& data, const std::vector<std::string> &values) {
    data.lmontiqn = generateRandomValue<int>();
    data.gttsakbp = generateRandomValue<int>();
    data.sgruersi = generateRandomValue<float>();
    data.cbjiwmfv = generateRandomValue<float>();
    data.toiywwtb = values[0];
    data.ojkinvvf = values[1];
    for(int i = 0; i < 3; i++) {
        data.mjogvdtj[i].etiizwwn = generateRandomValue<int>();
        data.mjogvdtj[i].cbcfskih = generateRandomValue<int>();
        data.mjogvdtj[i].ldeucjga = generateRandomValue<float>();
        data.mjogvdtj[i].cgekyebx = generateRandomValue<float>();
        data.mjogvdtj[i].xgrdxjrt = values[(i + 1) * 2 + 0];
        data.mjogvdtj[i].calizksb = values[(i + 1) * 2 + 1];
    }
}
