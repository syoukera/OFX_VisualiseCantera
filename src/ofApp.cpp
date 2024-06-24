#include "ofApp.h"

void ofApp::setup(){

	ofTrueTypeFont::setGlobalDpi(72);

	verdana14.load("verdana.ttf", 14, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);

    // mole fractionデータのCSVファイルの読み込み
    if (!moleFractionDataLoader.loadData("H2O2_X.csv")) {
        ofLogError("ofApp::setup") << "data_H2O2_Ignition_X_wo_header.csv";
    }

    // positionデータのCSVファイルの読み込み
    if (!positionDataLoader.loadData("H2O2_positions.csv")) {
        ofLogError("ofApp::setup") << "Failed to load data_positions.csv";
    }

    // spacies nameデータのCSVファイルの読み込み
    if (!speciesNameDataLoader.loadData("H2O2_name_species.csv")) {
        ofLogError("ofApp::setup") << "Failed to load name_species.csv";
    }

    // timeデータのCSVファイルの読み込み
    if (!timeDataLoader.loadData("H2O2_time.csv")) {
        ofLogError("ofApp::setup") << "Failed to load data_H2O2_Ignition_time.csv";
    }

    // temperatureデータのCSVファイルの読み込み
    if (!tempDataLoader.loadData("H2O2_T.csv")) {
        ofLogError("ofApp::setup") << "Failed to load data_H2O2_Ignition_T.csv";
    }

    // Speciesデータの読み込み
    loadSpeciesData();
    
    // GUIの設定
    setupGui();
    
    // 初期行を設定
    currentRow = 0;

    // マウス座標の初期化
    mouseX = mouseY = 0;
}

void ofApp::update(){
    // 行を進める
    currentRow = (currentRow + 1) % timeDataLoader.getNumRows();
}

void ofApp::draw(){
    ofBackground(255); // 背景を白色に設定

    // GUIの描画
    gui.draw();

	float time        = timeDataLoader.getRow(currentRow)[0];
	float temperature = tempDataLoader.getRow(currentRow)[0];

	verdana14.drawString("Time [s]:        ", 35, 35);
	verdana14.drawString("Temperature [k]: ", 35, 65);

	verdana14.drawString(ofToString(time), 200, 35);
	verdana14.drawString(ofToString(temperature), 200, 65);


    // 各Speciesを描画
    for (size_t i = 0; i < speciesList.size(); ++i) {
        if (speciesToggles[i]) { // トグルボタンがオンの場合に描画
            speciesList[i].draw(currentRow);
            if (speciesList[i].isMouseOver(mouseX, mouseY, currentRow)) {
                speciesList[i].drawMouseOverInfo(mouseX, mouseY, currentRow);
            }
        }
    }
}

void ofApp::mouseMoved(int x, int y){
    mouseX = x;
    mouseY = y;
}

void ofApp::loadSpeciesData() {
    // データローダーからSpeciesデータを読み込む
    size_t numRows = moleFractionDataLoader.getNumRows();
    size_t numCols = moleFractionDataLoader.getRow(0).size();

    // 仮のデータとしてSpeciesのリストを作成
    for (size_t i = 0; i < numCols; ++i) {
        std::string name = speciesNameDataLoader.getLabel(i);

        float x = positionDataLoader.getRow(i)[0]*ofGetWidth();
        float y = positionDataLoader.getRow(i)[1]*ofGetHeight();
        // float x = ofMap(i, 0, numCols - 1, 50, ofGetWidth() - 50); // x座標を計算
        // float y = ofGetHeight() / 2; // y座標を中央に設定
        std::vector<float> molFractions;

        for (size_t j = 0; j < numRows; ++j) {
            molFractions.push_back(moleFractionDataLoader.getRow(j)[i]);
        }

        speciesList.emplace_back(name, x, y, molFractions);
    }
}

void ofApp::setupGui() {
    // GUIの初期設定
    gui.setup();

    // 各Speciesのトグルボタンを設定
    for (const auto& species : speciesList) {
        ofParameter<bool> toggle;
        toggle.set(species.getName(), true); // 初期状態をオンに設定
        gui.add(toggle); // トグルボタンをGUIに追加
        speciesToggles.push_back(toggle);
    }
}
