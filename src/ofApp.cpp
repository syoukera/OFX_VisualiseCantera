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

	int num_species = speciesNameDataLoader.getNumRows();
	// std::cout << num_species << std::endl;

	for (int k=0; k!=num_species; k++) {

        float x = positionDataLoader.getRow(k)[0]*ofGetWidth();
        float y = positionDataLoader.getRow(k)[1]*ofGetHeight();

        float moleFraction = moleFractionDataLoader.getRow(currentRow)[k];
		float size = moleFraction*100000;
		float radius = area2raduis(size);

		// std::cout << k << ' ' << name_species << ' ' << x << ' ' 
		// 		  << y << ' ' << radius << std::endl;
		// std::cout << name_species << std::endl;	

		float r = ofNoise(x, y)*255;
		float g = ofNoise(x*100, y)*255;
		float b = ofNoise(x, y*100)*255;

		// std::cout << k << " " << name_species << " " << r << std::endl;

		ofSetColor(r, g, b); // 色を黒に設定

		// std::cout << ofNoise(x, y) << std::endl;
		
		int numSegments = 100;
		// drawSmoothCircle(x, y, radius, numSegments);
		// // ofDrawCircle(x, y, radius); // 円を描画

        std::string name_species = speciesNameDataLoader.getLabel(k);

		ofSetColor(0);
		// verdana14.drawString(name_species, x, y);
	}

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

float ofApp::area2raduis(float area) {
		float radius = std::sqrt(area/PI);
		return radius;
}

void ofApp::drawSmoothCircle(float x, float y, float radius, int numSegments) {
    ofBeginShape();
    for (int i = 0; i!=numSegments; i++) {
        float angle = TWO_PI * i / numSegments;
        float dx = radius * cos(angle);
        float dy = radius * sin(angle);
        ofVertex(x + dx, y + dy);
    }
    ofEndShape(true); // trueを指定することで形を閉じます
}
