#pragma once

#include "ofMain.h"
#include <string>
#include <vector>

class Species {
public:
    Species(const std::string& name, float x, float y, const std::vector<float>& molFractions);

    void draw(int timeIndex, float maxArea) const;
    bool isMouseOver(float mouseX, float mouseY, int timeIndex) const;
    void drawMouseOverInfo(float mouseX, float mouseY, int timeIndex) const;
    const std::string& getName() const; // getNameメソッドの追加
    
    void mousePressed(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    void set_x(float new_value) {
        x = new_value;
    }
    float get_x(){
        return x;
    }
    void set_y(float new_value) {
        y = new_value;
    }
    float get_y(){
        return y;
    }

	ofTrueTypeFont	verdana14;
    

private:
    std::string name; // 化学種の名前
    float x, y; // x, y座標
    const float radius_base = 10.0; // 背景となる白い円とマウスオーバーの判定に使用する半径
    std::vector<float> molFractions; // モル分率の時系列データ
    
    bool bDragging; // ドラッグしているかどうか
    ofVec2f dragOffset; // ドラッグしているオフセット

	float area2radius(float area) const;
    void drawSmoothCircle(float x, float y, float radius, int numSegments = 100) const; // スムーズな円を描く関数
};
