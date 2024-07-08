#include "Reaction.h"

Reaction::Reaction(const std::vector<Species>& speciesList)
    : speciesList(speciesList) {}

void Reaction::draw(int startIdx, int endIdx, int currentRow, float lineWidth, float lineHeight) const {
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

	ofSetColor(125, 125, 125); // Set the drawing color to white
	ofSetLineWidth(lineWidth);
	ofDrawLine(startX, startY+lineHeight, endX, endY+lineHeight);
}
