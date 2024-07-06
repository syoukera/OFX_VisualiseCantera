#include "Species.h"

Species::Species(const std::string& name, float x, float y, const std::vector<float>& molFractions)
    : name(name), x(x), y(y), molFractions(molFractions) {

	ofTrueTypeFont::setGlobalDpi(72);

	verdana14.load("verdana.ttf", 20, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);

	}

void Species::draw(int timeIndex, float maxArea) const {
    if (timeIndex < 0 || timeIndex >= molFractions.size()) {
        ofLogError("Species::draw") << "Time index out of bounds";
        return;
    }


	int numSegments = 100;

    // draw white circle
    
	ofSetColor(255);
	drawSmoothCircle(x, y, radius_base, numSegments); // 円を描画

    // draw color circle related to mole fraction

    float molFraction = molFractions[timeIndex];
    float area = ofMap(molFraction, 0, 1, 0, maxArea); // モル分率を0から10000の面積にマッピング
	float radius = area2radius(area);
    
	float r = ofNoise(x, y)*255;
	float g = ofNoise(x*100, y)*255;
	float b = ofNoise(x, y*100)*255;
	ofSetColor(r, g, b);

	drawSmoothCircle(x, y, radius, numSegments); // 円を描画

    // draw species name
	ofSetColor(0);
	verdana14.drawString(name, x-7, y+7); // 化学種の名前を描画
}

bool Species::isMouseOver(float mouseX, float mouseY, int timeIndex) const {
    if (timeIndex < 0 || timeIndex >= molFractions.size()) {
        return false;
    }

    float dx = mouseX - x;
    float dy = mouseY - y;
    float distance = sqrt(dx * dx + dy * dy);
    return distance <= radius_base;
}

void Species::drawMouseOverInfo(float mouseX, float mouseY, int timeIndex) const {
    if (timeIndex < 0 || timeIndex >= molFractions.size()) {
        return;
   }

    float molFraction = molFractions[timeIndex];
    std::string info = "Mol Fraction: " + ofToString(molFraction, 4);
    ofSetColor(255, 0, 0); // 色を赤に設定
    ofDrawBitmapString(info, mouseX + 10, mouseY - 10);
}

const std::string& Species::getName() const {
    return name;
}

float Species::area2radius(float area) const {
		float radius = std::sqrt(area/PI);
		return radius;
}

void Species::drawSmoothCircle(float x, float y, float radius, int numSegments) const {
    ofBeginShape();
    for (int i = 0; i < numSegments; ++i) {
        float theta = 2.0f * PI * float(i) / float(numSegments); // 2πをnumSegmentsに分割
        float dx = radius * cosf(theta); // x座標
        float dy = radius * sinf(theta); // y座標
        ofVertex(x + dx, y + dy);
    }
    ofEndShape(true); // 最後の頂点を最初の頂点に接続
}