#include "DataLoader.h"
#include "ofMain.h"

bool DataLoader::loadData(const std::string& filePath) {
    if (csv.load(filePath)) {
        ofLogNotice("DataLoader::loadData") << "CSV loaded successfully from " << filePath;
        parseCsv();
        return true;
    } else {
        ofLogError("DataLoader::loadData") << "Unable to load CSV file from " << filePath;
        return false;
    }
}

void DataLoader::parseCsv() {
    data.clear();
    for (size_t i = 0; i < csv.getNumRows(); ++i) {
        std::vector<float> row;
        for (size_t j = 0; j < csv.getNumCols(i); ++j) {
            row.push_back(ofToFloat(csv[i][j])); // 各列からデータを取得
        }
        data.push_back(row);
    }
}

const std::vector<float>& DataLoader::getRow(size_t row) const {
    return data.at(row);
}

size_t DataLoader::getNumRows() const {
    return data.size();
}

bool LabelLoader::loadData(const std::string& filePath) {
    if (csv.load(filePath)) {
        ofLogNotice("LabelLoader::loadData") << "CSV loaded successfully from " << filePath;
        parseCsv();
        return true;
    } else {
        ofLogError("LabelLoader::loadData") << "Unable to load CSV file from " << filePath;
        return false;
    }
}

void LabelLoader::parseCsv() {
    labels.clear();
    for (size_t i = 0; i < csv.getNumRows(); ++i) {
        labels.push_back(csv[i][0]); // 0番目の列からラベルを取得
    }
}

const std::string& LabelLoader::getLabel(size_t row) const {
    return labels.at(row);
}

size_t LabelLoader::getNumRows() const {
    return labels.size();
}