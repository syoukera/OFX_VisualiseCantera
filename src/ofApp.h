#pragma once

#include "ofMain.h"
#include "ofxCsv.h"
#include "MyClass.h"
#include "DataLoader.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

	float area2raduis(float area);
	void drawSmoothCircle(float x, float y, float radius, int numSegments);
    
	ofTrueTypeFont	verdana14;

    ofxCsv csv; // CSVデータを読み込むためのオブジェクト
    // ofxCsv csv_species; // CSVデータを読み込むためのオブジェクト
    // ofxCsv csv_time; // CSVデータを読み込むためのオブジェクト
    // ofxCsv csv_temperature; // CSVデータを読み込むためのオブジェクト

    int currentRow; // 現在の行を追跡するための変数
    
    std::vector<std::string> speciesNameVec; // species nameのベクトル
    std::vector<float> tempVec; // temperatureのベクトル
    std::vector<float> timeVec; // timeのベクトル
    std::vector<std::vector<float>> positionMat; // XYのベクトル
    std::vector<std::vector<float>> moleFractionMat; // モル分率のベクトル

private:
    MyClass myClass;  // 新しいクラスのインスタンスを追加
    
    void loadData(const std::string& filePath, std::vector<float>& data); // floatデータ読み込み関数
    void loadData(const std::string& filePath, std::vector<std::string>& data); // stringデータ読み込み関数
    void loadData(const std::string& filePath, std::vector<std::vector<float>>& data); // 2次元floatデータ読み込み関数

    DataLoader tempDataLoader; // temperatureデータのローダー
    DataLoader timeDataLoader; // timeデータのローダー
    LabelLoader speciesNameDataLoader; // speciesNameデータのローダー
};