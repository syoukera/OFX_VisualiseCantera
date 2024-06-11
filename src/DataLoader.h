#pragma once

#include "ofxCsv.h"
#include <vector>
#include <string>

class DataLoader {
public:
    // データを読み込むメンバ関数
    bool loadData(const std::string& filePath);

    // 一行分のデータを取得するメンバ関数
    const std::vector<float>& getRow(size_t row) const;

    // 行数を取得するメンバ関数
    size_t getNumRows() const;

private:
    ofxCsv csv; // CSVデータを読み込むためのオブジェクト
    std::vector<std::vector<float>> data; // 2次元データのベクトル

    void parseCsv(); // CSVデータを解析して内部データに格納するメンバ関数
};

class LabelLoader {
public:
    // データを読み込むメンバ関数
    bool loadData(const std::string& filePath);

    // 一行分のラベルを取得するメンバ関数
    const std::string& getLabel(size_t row) const;

    // 行数を取得するメンバ関数
    size_t getNumRows() const;

private:
    ofxCsv csv; // CSVデータを読み込むためのオブジェクト
    std::vector<std::string> labels; // ラベルデータのベクトル

    void parseCsv(); // CSVデータを解析して内部データに格納するメンバ関数
};