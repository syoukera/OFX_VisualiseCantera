#include "Species.h"

Species::Species(const std::string& name, float x, float y, const std::vector<float>& molFractions)
    : name(name), x(x), y(y), molFractions(molFractions) {

	ofTrueTypeFont::setGlobalDpi(72);

	verdana14.load("verdana.ttf", 14, true, true);
	verdana14.setLineHeight(18.0f);
	verdana14.setLetterSpacing(1.037);

	}

void Species::draw(int timeIndex) const {
    if (timeIndex < 0 || timeIndex >= molFractions.size()) {
        ofLogError("Species::draw") << "Time index out of bounds";
        return;
    }

    float molFraction = molFractions[timeIndex];
    float area = ofMap(molFraction, 0, 1, 0, 100000); // モル分率を0から50の半径にマッピング
	float radius = area2raduis(area);

	float r = ofNoise(x, y)*255;
	float g = ofNoise(x*100, y)*255;
	float b = ofNoise(x, y*100)*255;
	ofSetColor(r, g, b);

	int numSegments = 100;
	drawSmoothCircle(x, y, radius, numSegments);
    // ofDrawCircle(x, y, radius); // 円を描画
	
	ofSetColor(0);
	verdana14.drawString(name, x - radius, y - radius - 10);
    // ofDrawBitmapString(name, x - radius, y - radius - 10); // 化学種の名前を描画
}

float Species::area2raduis(float area) const {
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