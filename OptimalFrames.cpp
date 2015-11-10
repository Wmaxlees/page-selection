//
// Created by William Lees on 11/10/15.
//

#include "OptimalFrames.h"

OptimalFrames::OptimalFrames(int capacity) : Frames(capacity) {}

bool OptimalFrames::add(PageNode node) {
    // Check if we have an open frame or the page is already loaded
    for (int i = 0; i < this->m_Capacity; ++i) {
        if (this->m_pFrames[i].getPageID() == node.getPageID()) {
            this->m_pFrames[i] = node;
            return false;
        }
    }

    for (int i = 0; i < this->m_Capacity; ++i) {
        if (this->m_pFrames[i].getPageID() == 0) {
            this->m_pFrames[i] = node;
            return true;
        }
    }

    // If code gets here, a replacement needs to take place
    int index = 0;
    for (int i = 1; i < this->m_Capacity; ++i) {
        // Check if this page isn't needed ever again
        if (this->m_pFrames[i].getChild() == nullptr) {
            this->m_pFrames[i] = node;
            return true;
        }

        // Otherwise compare who has the latest use
        if (this->m_pFrames[i].getChild()->getIndex() > this->m_pFrames[index].getChild()->getIndex()) {
            index = i;
        }
    }
    this->m_pFrames[index] = node;
    return true;
}