#pragma once

#include "ofMain.h"
#include <string>
#include <vector>

class Species {
public:
    Species(const std::string& name, float x, float y, const std::vector<float>& molFractions);

    void draw(int timeIndex) const;

private:
    std::string name; // 化学種の名前
    float x; // x座標
    float y; // y座標
    std::vector<float> molFractions; // モル分率の時系列データ
};
