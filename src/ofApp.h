#pragma once

#include "ofMain.h"
#include "BaseLoader.h"
#include "Species.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
 
	ofTrueTypeFont	verdana14;

    int currentRow; // 現在の行を追跡するための変数
    
    std::vector<std::vector<float>> moleFractionMat; // モル分率のベクトル

private:
    
    DataLoader tempDataLoader; // temperatureデータのローダー
    DataLoader timeDataLoader; // timeデータのローダー
    DataLoader positionDataLoader; // positionデータのローダー
    DataLoader moleFractionDataLoader; // mole fractionデータのローダー
    LabelLoader speciesNameDataLoader; // speciesNameデータのローダー

    std::vector<Species> speciesList; // Speciesのリスト

    void loadSpeciesData();
};