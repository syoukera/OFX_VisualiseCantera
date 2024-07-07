#pragma once
#include "ofMain.h"
#include "Species.h"
#include <vector>

class Reaction {
public:
    Reaction(const std::vector<Species>& speciesList);

    void draw(int startIdx, int endIdx, int currentRow, float rop, int numShownReactions) const;

private:
    const std::vector<Species>& speciesList;
};