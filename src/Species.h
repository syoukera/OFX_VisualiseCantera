#pragma once

#include "ofMain.h"
#include <string>
#include <vector>

class Species {
public:
    Species(const std::string& name, float x, float y, const std::vector<float>& molFractions);

    void draw(int timeIndex) const;

	ofTrueTypeFont	verdana14;

private:
    std::string name; // 化学種の名前
    float x; // x座標
    float y; // y座標
    std::vector<float> molFractions; // モル分率の時系列データ

	float area2raduis(float area) const;
	// void drawSmoothCircle(float x, float y, float radius, int numSegments) const;
    void drawSmoothCircle(float x, float y, float radius, int numSegments = 100) const; // スムーズな円を描く関数
};
