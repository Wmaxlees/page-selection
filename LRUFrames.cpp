//
// Created by William Lees on 11/10/15.
//

#include "LRUFrames.h"

LRUFrames::LRUFrames(int capacity) : Frames(capacity) {}

bool LRUFrames::add(PageNode node) {
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
        if (this->m_pFrames[i].getLastCalled() < this->m_pFrames[index].getLastCalled()) {
            index = i;
        }
    }
    this->m_pFrames[index] = node;
    return true;
}