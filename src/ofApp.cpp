#include "ofMain.h"
#include "ofApp.h"

void ofApp::setup(){

	ofTrueTypeFont::setGlobalDpi(72);

	verdana14.load("verdana.ttf", 14, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);

    // mole fractionデータのCSVファイルの読み込み
    if (!moleFractionDataLoader.loadData("data_H2O2_Ignition_X_wo_header.csv")) {
        ofLogError("ofApp::setup") << "data_H2O2_Ignition_X_wo_header.csv";
    }

    // positionデータのCSVファイルの読み込み
    if (!positionDataLoader.loadData("data_positions.csv")) {
        ofLogError("ofApp::setup") << "Failed to load data_positions.csv";
    }

    // spacies nameデータのCSVファイルの読み込み
    if (!speciesNameDataLoader.loadData("name_species.csv")) {
        ofLogError("ofApp::setup") << "Failed to load name_species.csv";
    }

    // timeデータのCSVファイルの読み込み
    if (!timeDataLoader.loadData("data_H2O2_Ignition_time.csv")) {
        ofLogError("ofApp::setup") << "Failed to load data_H2O2_Ignition_time.csv";
    }

    // temperatureデータのCSVファイルの読み込み
    if (!tempDataLoader.loadData("data_H2O2_Ignition_T.csv")) {
        ofLogError("ofApp::setup") << "Failed to load data_H2O2_Ignition_T.csv";
    }

    // Speciesデータの読み込み
    loadSpeciesData();

    // 初期行を設定
    currentRow = 0;
}

void ofApp::update(){
    // 行を進める
    currentRow = (currentRow + 1) % timeDataLoader.getNumRows();
}

void ofApp::draw(){
    
    ofBackground(255); // 背景を白色に設定

	float time        = timeDataLoader.getRow(currentRow)[0];
	float temperature = tempDataLoader.getRow(currentRow)[0];

	verdana14.drawString("Time [s]:        ", 35, 35);
	verdana14.drawString("Temperature [k]: ", 35, 65);

	verdana14.drawString(ofToString(time), 200, 35);
	verdana14.drawString(ofToString(temperature), 200, 65);

    // 各Speciesを描画
    for (const auto& species : speciesList) {
        species.draw(currentRow);
    }

}

void ofApp::loadSpeciesData() {
    // データローダーからSpeciesデータを読み込む
    size_t numRows = moleFractionDataLoader.getNumRows();
    size_t numCols = moleFractionDataLoader.getRow(0).size();

    // 仮のデータとしてSpeciesのリストを作成
    // ここでは、xとy座標、名前、およびモル分率のデータを手動で設定
    // 実際には、データローダーからこれらの情報を取得する
    for (size_t i = 0; i < numCols; ++i) {
        std::string name = speciesNameDataLoader.getLabel(i);

        // float x = ofMap(i, 0, numCols - 1, 50, ofGetWidth() - 50); // x座標を計算
        // float y = ofGetHeight() / 2; // y座標を中央に設定
        float x = positionDataLoader.getRow(i)[0]*ofGetWidth();
        float y = positionDataLoader.getRow(i)[1]*ofGetHeight();

        std::vector<float> molFractions;

        for (size_t j = 0; j < numRows; ++j) {
            molFractions.push_back(moleFractionDataLoader.getRow(j)[i]);
        }

        speciesList.emplace_back(name, x, y, molFractions);
    }
}