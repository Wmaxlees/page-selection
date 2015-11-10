//
// Created by William Lees on 11/10/15.
//

#ifndef PAGE_SELECTION_OPTIMALFRAMES_H
#define PAGE_SELECTION_OPTIMALFRAMES_H

#include "Frames.h"

class OptimalFrames : public Frames {
public:
    OptimalFrames(int capacity);
    bool add(PageNode node);
};


#endif //PAGE_SELECTION_OPTIMALFRAMES_H
