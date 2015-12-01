//
// Created by William Lees on 11/10/15.
//

#ifndef PAGE_SELECTION_LRUFRAMES_H
#define PAGE_SELECTION_LRUFRAMES_H

#include "Frames.h"

class LRUFrames : public Frames {
public:
    LRUFrames(int capacity);
    bool add(PageNode *node);
};


#endif //PAGE_SELECTION_LRUFRAMES_H
