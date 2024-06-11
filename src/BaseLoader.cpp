#include "BaseLoader.h"
#include "ofMain.h"

bool BaseLoader::loadData(const std::string& filePath) {
    if (csv.load(filePath)) {
        ofLogNotice("BaseLoader::loadData") << "CSV loaded successfully from " << filePath;
        parseCsv();
        return true;
    } else {
        ofLogError("BaseLoader::loadData") << "Unable to load CSV file from " << filePath;
        return false;
    }
}

size_t BaseLoader::getNumRows() const {
    return csv.getNumRows();
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

void LabelLoader::parseCsv() {
    labels.clear();
    for (size_t i = 0; i < csv.getNumRows(); ++i) {
        labels.push_back(csv[i][0]); // 0番目の列からラベルを取得
    }
}

const std::string& LabelLoader::getLabel(size_t row) const {
    return labels.at(row);
}
