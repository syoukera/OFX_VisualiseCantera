#pragma once

#include "ofMain.h"
#include "ofxCsv.h"
#include "ofApp.h"

void ofApp::setup(){

	ofTrueTypeFont::setGlobalDpi(72);

	verdana14.load("verdana.ttf", 14, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);

    // CSVファイルの読み込み
    // std::string name_csv = "export_H2O2_Ignition_X.csv";
    // std::string name_csv = "export_H2O2_Ignition_X_woHeader.csv";

    std::string name_csv             = "data_H2O2_Ignition_X_wo_header.csv";
    std::string name_csv_species     = "name_species2.csv";
    std::string name_csv_time        = "data_H2O2_Ignition_time.csv";
    std::string name_csv_temperature = "data_H2O2_Ignition_T.csv";

    if(csv.load(name_csv)) {
        ofLogNotice("ofApp::setup") << "CSV loaded successfully.";
    } else {
        ofLogError("ofApp::setup") << "Unable to load CSV file.";
    }

    if(csv_species.load(name_csv_species)) {
        ofLogNotice("ofApp::setup") << "CSV loaded successfully.";
    } else {
        ofLogError("ofApp::setup") << "Unable to load CSV file.";
    }
    
    loadData(name_csv_time, timeVec);

    loadData(name_csv_temperature, tempVec);

    // 初期行を設定
    currentRow = 0;

    myClass.doSomething();  // 新しいクラスのメソッドを呼び出し
}

void ofApp::update(){
    // 行を進める
    currentRow = (currentRow + 1) % csv.getNumRows();
}

void ofApp::draw(){
    
    ofBackground(255); // 背景を白色に設定

	int num_species = csv_species.getNumCols();
	// std::cout << num_species << std::endl;

	for (int k=0; k!=num_species; k++) {

		std::string name_species = csv_species[0][k];
		float x = std::stof(csv_species[1][k])*ofGetWidth();
		float y = std::stof(csv_species[2][k])*ofGetHeight();

		float size = std::stof(csv[currentRow][k])*100000;
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
		drawSmoothCircle(x, y, radius, numSegments);
		// ofDrawCircle(x, y, radius); // 円を描画

		ofSetColor(0);
		verdana14.drawString(name_species, x, y);
	}

	// std::string time_str = std::_Floating_to_string("%.3f", time);
	// std::string time_str = csv_time[currentRow][0];
	// std::string temperature_str = csv_temperature[currentRow][0];

	// float time = std::stof(time_str);
	// float temperature = std::stof(temperature_str);

	verdana14.drawString("Time [s]:        ", 35, 35);
	verdana14.drawString("Temperature [k]: ", 35, 65);

	verdana14.drawString(ofToString(timeVec[currentRow]), 200, 35);
	verdana14.drawString(ofToString(tempVec[currentRow]), 200, 65);
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

void ofApp::loadData(const std::string& filePath, std::vector<float>& data) {
    ofxCsv csv;
    if (csv.load(filePath)) {
        ofLogNotice("ofApp::loadData") << "CSV loaded successfully from " << filePath;
        for (int i = 0; i < csv.getNumRows(); i++) {
            data.push_back(ofToFloat(csv[i][0])); // 0番目の列からデータを取得
        }
    } else {
        ofLogError("ofApp::loadData") << "Unable to load CSV file from " << filePath;
    }
}