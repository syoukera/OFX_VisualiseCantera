#include "ofApp.h"

void ofApp::setup(){

	ofTrueTypeFont::setGlobalDpi(72);

	verdana14.load("verdana.ttf", 14, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);

    // mole fractionデータのCSVファイルの読み込み
    if (!moleFractionDataLoader.loadData("H2O2_X.csv")) {
        ofLogError("ofApp::setup") << "H2O2_X.csv";
    }

    // positionデータのCSVファイルの読み込み
    if (!positionDataLoader.loadData("H2O2_positions.csv")) {
        ofLogError("ofApp::setup") << "Failed to load H2O2_positions.csv";
    }

    // spacies nameデータのCSVファイルの読み込み
    if (!speciesNameDataLoader.loadData("H2O2_name_species.csv")) {
        ofLogError("ofApp::setup") << "Failed to load H2O2_name_species.csv";
    }

    // timeデータのCSVファイルの読み込み
    if (!timeDataLoader.loadData("H2O2_time.csv")) {
        ofLogError("ofApp::setup") << "Failed to load H2O2_time.csv";
    }

    // temperatureデータのCSVファイルの読み込み
    if (!tempDataLoader.loadData("H2O2_T.csv")) {
        ofLogError("ofApp::setup") << "Failed to load H2O2_T.csv";
    }


    // temperatureデータのCSVファイルの読み込み
    if (!ropDataLoader.loadData("H2O2_ROP.csv")) {
        ofLogError("ofApp::setup") << "Failed to load H2O2_ROP.csv";
    }

    // temperatureデータのCSVファイルの読み込み
    if (!muDataLoader.loadData("H2O2_mu.csv")) {
        ofLogError("ofApp::setup") << "Failed to load H2O2_mu.csv";
    }

    // temperatureデータのCSVファイルの読み込み
    if (!reactionEquationDataLoader.loadData("H2O2_ROP.csv")) {
        ofLogError("ofApp::setup") << "Failed to load H2O2_ROP.csv";
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

    size_t startIndex, endIndex;

    // StartのSpeciesを描画
    for (size_t i = 0; i < speciesList.size(); ++i) {
        if (speciesTogglesStart[i]) { // Startトグルボタンがオンの場合に描画
            speciesList[i].draw(currentRow);
            if (speciesList[i].isMouseOver(mouseX, mouseY, currentRow)) {
                speciesList[i].drawMouseOverInfo(mouseX, mouseY, currentRow);
            }
            startIndex = i;
        }
    }

    // EndのSpeciesを描画
    for (size_t i = 0; i < speciesList.size(); ++i) {
        if (speciesTogglesEnd[i]) { // Endトグルボタンがオンの場合に描画
            speciesList[i].draw(currentRow);
            if (speciesList[i].isMouseOver(mouseX, mouseY, currentRow)) {
                speciesList[i].drawMouseOverInfo(mouseX, mouseY, currentRow);
            }
            endIndex = i;
        }
    }

    // std::cout << startIndex << " " << endIndex << std::endl;
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

    // StartのSpeciesのトグルボタンを設定
    for (size_t i = 0; i < speciesList.size(); ++i) {
        ofParameter<bool> toggleStart;
        toggleStart.set(speciesList[i].getName() + " Start", false); // 初期状態をオフに設定
        speciesTogglesStart.push_back(toggleStart);
        gui.add(toggleStart);
        auto listenerStart = std::make_shared<ofEventListener>(toggleStart.newListener([this, i](bool & value) {
            toggleChangedStart(value, i);
        }));
        toggleListenersStart.push_back(listenerStart);
    }

    // EndのSpeciesのトグルボタンを設定
    for (size_t i = 0; i < speciesList.size(); ++i) {
        ofParameter<bool> toggleEnd;
        toggleEnd.set(speciesList[i].getName() + " End", false); // 初期状態をオフに設定
        speciesTogglesEnd.push_back(toggleEnd);
        gui.add(toggleEnd);
        auto listenerEnd = std::make_shared<ofEventListener>(toggleEnd.newListener([this, i](bool & value) {
            toggleChangedEnd(value, i);
        }));
        toggleListenersEnd.push_back(listenerEnd);
    }
}

void ofApp::toggleChangedStart(bool & value, int index) {
    if (value) {
        for (size_t i = 0; i < speciesTogglesStart.size(); ++i) {
            if (i != index) {
                speciesTogglesStart[i].setWithoutEventNotifications(false); // 他のトグルをオフにする
            }
        }
        ofLogNotice("ofApp") << "Start Toggle changed: Only one start species can be active at a time";
    }
}

void ofApp::toggleChangedEnd(bool & value, int index) {
    if (value) {
        for (size_t i = 0; i < speciesTogglesEnd.size(); ++i) {
            if (i != index) {
                speciesTogglesEnd[i].setWithoutEventNotifications(false); // 他のトグルをオフにする
            }
        }
        ofLogNotice("ofApp") << "End Toggle changed: Only one end species can be active at a time";
    }
}