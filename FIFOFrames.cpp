//
// Created by William Lees on 11/9/15.
//

#include "FIFOFrames.h"

FIFOFrames::FIFOFrames(int capacity) : Frames(capacity) {
    this->m_LastFrame = -1;
}

// Returns true if there was a page fault
bool FIFOFrames::add(PageNode node) {
    // Check if we have an open frame or the page is already loaded
    for (int i = 0; i < this->m_Capacity; ++i) {
        if (this->m_pFrames[i].getPageID() == node.getPageID()) {
            this->m_pFrames[i] = node;
            return false;
        }

        if (this->m_pFrames[i].getPageID() == 0) {
            this->m_pFrames[i] = node;
            return true;
        }
    }

    // If code gets here, a replacement needs to take place
    this->m_LastFrame = (this->m_LastFrame + 1) % this->m_Capacity;
    this->m_pFrames[this->m_LastFrame] = node;
    return true;
}