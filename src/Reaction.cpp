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

    // get x, y at start point
    float startSpeciesX = startSpecies.getX();
    float startSpeciesY = startSpecies.getY();

    // get x, y at end point
    float endSpeciesX = endSpecies.getX();
    float endSpeciesY = endSpecies.getY();

    // get x, y at fold point on start species
    float startTheta = asin(lineHeight/foldRadious);
    float startFoldX = startSpeciesX + foldRadious*cos(startTheta);
    float startFoldY = startSpeciesY + foldRadious*sin(startTheta);

    // get x, y at fold point on end species
    float endTheta = asin(lineHeight/foldRadious);
    float endFoldX = endSpeciesX - foldRadious*cos(endTheta);
    float endFoldY = endSpeciesY + foldRadious*sin(endTheta);

    // get x, y at start point
    float startEdgeX = startSpeciesX + edgeRadious*cos(startTheta);
    float startEdgeY = startSpeciesY + edgeRadious*sin(startTheta);

    // get x, y at end point
    float endEdgeX = endSpeciesX - edgeRadious*cos(endTheta);
    float endEdgeY = endSpeciesY + edgeRadious*sin(endTheta);
    
	ofSetColor(125, 125, 125); // Set the drawing color to white
	ofSetLineWidth(lineWidth);

    // ofBeginShape();

    // ofVertex(startEdgeX, startEdgeY);
    // ofVertex(startFoldX, startFoldY);
    // ofVertex(endFoldX, endFoldY);
    // ofVertex(endEdgeX, endEdgeY);
    // ofEndShape(false);

	ofDrawLine(startEdgeX, startEdgeY, startFoldX, startFoldY);
	ofDrawLine(startFoldX, startFoldY, endFoldX, endFoldY);
	ofDrawLine(endFoldX, endFoldY, endEdgeX, endEdgeY);
}
