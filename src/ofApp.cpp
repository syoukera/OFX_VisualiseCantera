#include "ofApp.h"

void ofApp::setup(){

	ofTrueTypeFont::setGlobalDpi(72);

	verdana14.load("verdana.ttf", 14, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);

    // データのCSVファイルの読み込み

    if (!moleFractionDataLoader.loadData("H2O2_X.csv")) {
        ofLogError("ofApp::setup") << "H2O2_X.csv";
    }

    if (!positionDataLoader.loadData("H2O2_positions.csv")) {
        ofLogError("ofApp::setup") << "Failed to load H2O2_positions.csv";
    }

    if (!speciesNameDataLoader.loadData("H2O2_name_species.csv")) {
        ofLogError("ofApp::setup") << "Failed to load H2O2_name_species.csv";
    }

    if (!timeDataLoader.loadData("H2O2_time.csv")) {
        ofLogError("ofApp::setup") << "Failed to load H2O2_time.csv";
    }

    if (!tempDataLoader.loadData("H2O2_T.csv")) {
        ofLogError("ofApp::setup") << "Failed to load H2O2_T.csv";
    }

    if (!ropDataLoader.loadData("H2O2_ROP.csv")) {
        ofLogError("ofApp::setup") << "Failed to load H2O2_ROP.csv";
    }

    if (!muDataLoader.loadData("H2O2_mu.csv")) {
        ofLogError("ofApp::setup") << "Failed to load H2O2_mu.csv";
    }

    if (!reactionEquationDataLoader.loadData("H2O2_reaction_equations.csv")) {
        ofLogError("ofApp::setup") << "Failed to load H2O2_reaction_equations.csv";
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
            startIndex = i;
        }
    }

    // EndのSpeciesを描画
    for (size_t i = 0; i < speciesList.size(); ++i) {
        if (speciesTogglesEnd[i]) { // Endトグルボタンがオンの場合に描画
            endIndex = i;

            // データローダーからmuデータを読み込む
            size_t numSpecies = muDataLoader.getNumRows();
            size_t numReactions = muDataLoader.getRow(0).size();

            int numShownReactions = 0;

            // 仮のデータとしてSpeciesのリストを作成
            for (size_t i = 0; i < numReactions; ++i) {

                float muStart = muDataLoader.getRow(startIndex)[i];
                float muEnd = muDataLoader.getRow(endIndex)[i];

                float xStart = speciesList[startIndex].get_x();
                float yStart  = speciesList[startIndex].get_y();
                float xEnd   = speciesList[endIndex].get_x();
                float yEnd   = speciesList[endIndex].get_y();

                float strideLineHeight = 10.0;

                // 反応物と生成物が選択されている時 = muの符号が異なる時
                if (muStart*muEnd < 0) {

                    // テストのために反応一つだけで描画
                    // if (i > 2) continue;

                    std::string reactionEquation = reactionEquationDataLoader.getLabel(i);

                    float rop = ropDataLoader.getRow(currentRow)[i];

                    ofSetColor(125, 125, 125); // Set the drawing color to white

                    float lineWidth = log(rop*1000);
                    ofSetLineWidth(lineWidth);

                    float lineHeightDiff = static_cast<float>(numShownReactions)*strideLineHeight;

                    ofDrawLine(xStart, yStart+lineHeightDiff, xEnd, yEnd+lineHeightDiff);

                    std::cout << i << " " << reactionEquation << " " << rop << " ";
                    // std::cout << startIndex << " " << endIndex << " ";
                    std::cout << numShownReactions << " " << lineHeightDiff << " ";
                    std::cout << muStart << " " << muEnd << std::endl;

                    numShownReactions++;
                }
            }
        }
    }

    float maxArea = 100000.0; // Speciesで描画される円の最大の面積

    // StartのSpeciesを描画
    for (size_t i = 0; i < speciesList.size(); ++i) {
        if (speciesTogglesStart[i]) { // Startトグルボタンがオンの場合に描画
            speciesList[i].draw(currentRow, maxArea);
            if (speciesList[i].isMouseOver(mouseX, mouseY, currentRow)) {
                speciesList[i].drawMouseOverInfo(mouseX, mouseY, currentRow);
            }
        }
    }

    // EndのSpeciesを描画
    for (size_t i = 0; i < speciesList.size(); ++i) {
        if (speciesTogglesEnd[i]) { // Endトグルボタンがオンの場合に描画
            speciesList[i].draw(currentRow, maxArea);
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

void ofApp::mousePressed(int x, int y, int button){
    for (auto& species : speciesList) {
        species.mousePressed(x, y, button);
    }
}

void ofApp::mouseDragged(int x, int y, int button){
    for (auto& species : speciesList) {
        species.mouseDragged(x, y, button);
    }
}

void ofApp::mouseReleased(int x, int y, int button){
    for (auto& species : speciesList) {
        species.mouseReleased(x, y, button);
    }
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

        speciesList.emplace_back(i, name, x, y, molFractions);
    }
}

void ofApp::setupGui() {
    // GUIの初期設定
    gui.setup();

    // StartのSpeciesのトグルボタンを設定
    for (size_t i = 0; i < speciesList.size(); ++i) {
        ofParameter<bool> toggleStart;
        if (i == 0) {
            toggleStart.set(speciesList[i].getName() + " Start", true); // 初期状態をトゥルーに設定
        } else {
            toggleStart.set(speciesList[i].getName() + " Start", false); // 初期状態をオフに設定
        }
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
        if (i == 1) {
            toggleEnd.set(speciesList[i].getName() + " Start", true); // 初期状態をトゥルーに設定
        } else {
            toggleEnd.set(speciesList[i].getName() + " Start", false); // 初期状態をオフに設定
        }
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
                // speciesTogglesEnd[i].setWithoutEventNotifications(false); // 他のトグルをオフにする
            }
        }
        ofLogNotice("ofApp") << "End Toggle changed: Only one end species can be active at a time";
    }
}