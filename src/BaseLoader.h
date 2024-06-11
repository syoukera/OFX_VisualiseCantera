#pragma once

#include "ofxCsv.h"
#include <vector>
#include <string>

class BaseLoader {
public:
    virtual bool loadData(const std::string& filePath);
    virtual size_t getNumRows() const;

protected:
    ofxCsv csv; // CSVデータを読み込むためのオブジェクト
    virtual void parseCsv() = 0; // 純粋仮想関数として宣言
};

class DataLoader : public BaseLoader {
public:
    const std::vector<float>& getRow(size_t row) const;

private:
    std::vector<std::vector<float>> data; // 2次元データのベクトル
    void parseCsv() override; // オーバーライドとして宣言
};

class LabelLoader : public BaseLoader {
public:
    const std::string& getLabel(size_t row) const;

private:
    std::vector<std::string> labels; // ラベルデータのベクトル
    void parseCsv() override; // オーバーライドとして宣言
};
