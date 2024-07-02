#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "BaseLoader.h"
#include "Species.h"
#include <vector>
#include <string>

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void mouseMoved(int x, int y);

private:

	ofTrueTypeFont	verdana14;

    int currentRow; // 現在の行を追跡するための変数
    
    std::vector<std::vector<float>> moleFractionMat; // モル分率のベクトル
    DataLoader tempDataLoader; // temperatureデータのローダー
    DataLoader timeDataLoader; // timeデータのローダー
    DataLoader positionDataLoader; // positionデータのローダー
    DataLoader moleFractionDataLoader; // mole fractionデータのローダー
    LabelLoader speciesNameDataLoader; // speciesNameデータのローダー

    DataLoader ropDataLoader; // ROPデータのローダー
    DataLoader muDataLoader; // equivalent coeffisientsデータのローダー
    LabelLoader reactionEquationDataLoader; // reaction equationデータのローダー

    std::vector<Species> speciesList; // Speciesのリスト
    float mouseX, mouseY; // マウスのx, y座標

    ofxPanel gui; // GUIパネル
    std::vector<ofParameter<bool>> speciesTogglesStart; // Start化学種の表示切替用トグルボタン
    std::vector<ofParameter<bool>> speciesTogglesEnd; // End化学種の表示切替用トグルボタン
    std::vector<std::shared_ptr<ofEventListener>> toggleListenersStart; // Startトグルリスナーのリスト
    std::vector<std::shared_ptr<ofEventListener>> toggleListenersEnd; // Endトグルリスナーのリスト

    void loadSpeciesData();
    void setupGui();
    void toggleChangedStart(bool & value, int index);
    void toggleChangedEnd(bool & value, int index);
};