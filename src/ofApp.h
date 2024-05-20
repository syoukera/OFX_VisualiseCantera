#pragma once

#include "ofMain.h"
#include "ofxCsv.h"
#include "MyClass.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

	float area2raduis(float area);
	void drawSmoothCircle(float x, float y, float radius, int numSegments);
    
	ofTrueTypeFont	verdana14;

    ofxCsv csv; // CSVデータを読み込むためのオブジェクト
    ofxCsv csv_species; // CSVデータを読み込むためのオブジェクト
    ofxCsv csv_time; // CSVデータを読み込むためのオブジェクト
    ofxCsv csv_temperature; // CSVデータを読み込むためのオブジェクト

    int currentRow; // 現在の行を追跡するための変数

private:
    MyClass myClass;  // 新しいクラスのインスタンスを追加
};