#include "Species.h"

Species::Species(const std::string& name, float x, float y, const std::vector<float>& molFractions)
    : name(name), x(x), y(y), molFractions(molFractions) {}

void Species::draw(int timeIndex) const {
    if (timeIndex < 0 || timeIndex >= molFractions.size()) {
        ofLogError("Species::draw") << "Time index out of bounds";
        return;
    }

    float molFraction = molFractions[timeIndex];
    float radius = ofMap(molFraction, 0, 1, 0, 50); // モル分率を0から50の半径にマッピング

    ofSetColor(0); // 色を黒に設定
    ofDrawCircle(x, y, radius); // 円を描画
    ofDrawBitmapString(name, x - radius, y - radius - 10); // 化学種の名前を描画
}
