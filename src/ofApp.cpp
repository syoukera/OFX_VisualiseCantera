#include "ofMain.h"
#include "ofxCsv.h"
#include "ofApp.h"

void ofApp::setup(){

	ofTrueTypeFont::setGlobalDpi(72);

	verdana14.load("verdana.ttf", 14, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);

    loadData("data_H2O2_Ignition_X_wo_header.csv", moleFractionMat);
    
    loadData("data_positions.csv", positionMat);

    loadData("name_species.csv", speciesNameVec);
    
    loadData("data_H2O2_Ignition_time.csv", timeVec);

    loadData("data_H2O2_Ignition_T.csv", tempVec);

    // 初期行を設定
    currentRow = 0;

    myClass.doSomething();  // 新しいクラスのメソッドを呼び出し
}

void ofApp::update(){
    // 行を進める
    currentRow = (currentRow + 1) % timeVec.size();
}

void ofApp::draw(){
    
    ofBackground(255); // 背景を白色に設定

	int num_species = speciesNameVec.size();
	// std::cout << num_species << std::endl;

	for (int k=0; k!=num_species; k++) {

		// std::string name_species = csv_species[0][k];
		std::string name_species = speciesNameVec[k];

		float x = positionMat[k][0]*ofGetWidth();
		float y = positionMat[k][1]*ofGetHeight();

        float moleFraction = moleFractionMat[currentRow][k];
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
		drawSmoothCircle(x, y, radius, numSegments);
		// ofDrawCircle(x, y, radius); // 円を描画

		ofSetColor(0);
		verdana14.drawString(speciesNameVec[k], x, y);
	}

	// std::string time_str = std::_Floating_to_string("%.3f", time);
	// std::string time_str = csv_time[currentRow][0];
	// std::string temperature_str = csv_temperature[currentRow][0];

	float time = timeVec[currentRow];
	float temperature = tempVec[currentRow];

	verdana14.drawString("Time [s]:        ", 35, 35);
	verdana14.drawString("Temperature [k]: ", 35, 65);

	verdana14.drawString(ofToString(time), 200, 35);
	verdana14.drawString(ofToString(temperature), 200, 65);
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
        for (size_t i = 0; i < csv.getNumRows(); i++) {
            data.push_back(ofToFloat(csv[i][0])); // 0番目の列からデータを取得
        }
    } else {
        ofLogError("ofApp::loadData") << "Unable to load CSV file from " << filePath;
    }
}

void ofApp::loadData(const std::string& filePath, std::vector<std::string>& data) {
    ofxCsv csv;
    if (csv.load(filePath)) {
        ofLogNotice("ofApp::loadData") << "CSV loaded successfully from " << filePath;
        for (size_t i = 0; i < csv.getNumRows(); i++) {
            data.push_back(csv[i][0]); // 0番目の列からデータを取得
        }
    } else {
        ofLogError("ofApp::loadData") << "Unable to load CSV file from " << filePath;
    }
}

void ofApp::loadData(const std::string& filePath, std::vector<std::vector<float>>& data) {
    ofxCsv csv;
    if (csv.load(filePath)) {
        ofLogNotice("ofApp::loadData") << "CSV loaded successfully from " << filePath;
        for (size_t i = 0; i < csv.getNumRows(); i++) {
            std::vector<float> row;
            for (size_t j = 0; j < csv.getNumCols(i); j++) {
                row.push_back(ofToFloat(csv[i][j])); // 各列からデータを取得
            }
            data.push_back(row);
        }
    } else {
        ofLogError("ofApp::loadData") << "Unable to load CSV file from " << filePath;
    }
}