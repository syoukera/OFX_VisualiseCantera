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

    std::vector<Species> speciesList; // Speciesのリスト
    float mouseX, mouseY; // マウスのx, y座標

    ofxPanel gui; // GUIパネル
    std::vector<ofParameter<bool>> speciesToggles; // 各Speciesの表示切替用トグルボタン

    void loadSpeciesData();
    void setupGui();
};
