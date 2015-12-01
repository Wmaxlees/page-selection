//
// Created by William Lees on 11/10/15.
//

#include "OptimalFrames.h"
#include <iostream>

OptimalFrames::OptimalFrames(int capacity) : Frames(capacity) {}

bool OptimalFrames::add(PageNode *node) {
    // Check if we have an open frame or the page is already loaded
    for (int i = 0; i < this->m_Capacity; ++i) {
        if (this->m_pFrames[i] == nullptr) {
            // std::cout << "Empty Frame" << std::endl;
            this->m_pFrames[i] = node;
            return true;
        }

        if (this->m_pFrames[i]->getPageID() == node->getPageID()) {
            // std::cout << "Already Framed" << std::endl;
            this->m_pFrames[i] = node;
            return false;
        }
    }

    // If code gets here, a replacement needs to take place
    int index = 0;
    for (int i = 1; i < this->m_Capacity; ++i) {
        if (this->m_pFrames[index]->getChild() == nullptr) {
            this->m_pFrames[index] = node;
            return true;
        }

        // std::cout << "Index: " << this->m_pFrames[index] << "->" << this->m_pFrames[index]->getChild() << std::endl;
        // std::cout << "I: " << this->m_pFrames[i] << "->" << this->m_pFrames[i]->getChild() << std::endl;

        // Check if this page isn't needed ever again
        if (this->m_pFrames[i]->getChild() == nullptr || ((size_t)this->m_pFrames[i]->getChild() & 0x0FFFFFFFFFFFFFFF) == 0x0) {
            // std::cout << "Replacing Frame With No Children" << std::endl;
            this->m_pFrames[i] = node;
            return true;
        }

        // Otherwise compare who has the latest use
        if (this->m_pFrames[i]->getChild()->getIndex() > this->m_pFrames[index]->getChild()->getIndex()) {
            // std::cout << "Using Frame With Longest Wait Time" << std::endl;
            index = i;
        }
    }

    this->m_pFrames[index] = node;
    return true;
}
