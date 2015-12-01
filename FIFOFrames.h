//
// Created by William Lees on 11/9/15.
//

#ifndef PAGE_SELECTION_FIFOFRAMES_H
#define PAGE_SELECTION_FIFOFRAMES_H

#include "Frames.h"

class FIFOFrames : public Frames {
public:
    FIFOFrames(int capacity);

    bool add(PageNode *node);

private:
    int m_LastFrame;
};


#endif //PAGE_SELECTION_FIFOFRAMES_H
