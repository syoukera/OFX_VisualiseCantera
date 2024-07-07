#include "Reaction.h"

Reaction::Reaction(const std::vector<Species>& speciesList)
    : speciesList(speciesList) {}

void Reaction::draw(int startIdx, int endIdx, int currentRow, float rop, int numShownReactions) const {
    if (startIdx < 0 || startIdx >= speciesList.size() || endIdx < 0 || endIdx >= speciesList.size()) {
        ofLogError("Reaction::draw") << "Invalid species index";
        return;
    }

    const Species& startSpecies = speciesList[startIdx];
    const Species& endSpecies = speciesList[endIdx];

    float startX = startSpecies.getX();
    float startY = startSpecies.getY();
    float endX = endSpecies.getX();
    float endY = endSpecies.getY();

    // // モル分率に基づいて反応の太さを設定
    // float startMolFraction = startSpecies.getMolFraction(currentRow);
    // float endMolFraction = endSpecies.getMolFraction(currentRow);
    // float thickness = ofMap(startMolFraction + endMolFraction, 0, 2, 1, 10);

    // ofSetLineWidth(thickness);
    // ofSetColor(255, 0, 0); // 反応を赤色で描画
    // ofDrawLine(startX, startY, endX, endY);


	// float rop = ropDataLoader.getRow(currentRow)[i];
	float strideLineHeight = 10.0;

	ofSetColor(125, 125, 125); // Set the drawing color to white

	float lineWidth = log(rop*1000);
	ofSetLineWidth(lineWidth);

	float lineHeightDiff = static_cast<float>(numShownReactions)*strideLineHeight;

	ofDrawLine(startX, startY+lineHeightDiff, endX, endY+lineHeightDiff);
}
