//
// Created by William Lees on 11/9/15.
//

#ifndef PAGE_SELECTION_FRAMES_H
#define PAGE_SELECTION_FRAMES_H

#include <iomanip>

#include "PageNode.h"

class Frames {
public:
    Frames(int capacity);
    virtual bool add(PageNode *node) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Frames& process);
protected:
    PageNode  **m_pFrames;
    int         m_Capacity;
};




#endif //PAGE_SELECTION_FRAMES_H
