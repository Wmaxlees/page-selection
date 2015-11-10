//
// Created by William Lees on 11/9/15.
//

#include "Frames.h"

Frames::Frames(int capacity) {
    this->m_pFrames = new PageNode[capacity];
    this->m_Capacity = capacity;
}

std::ostream& operator<<(std::ostream& os, const Frames& frames) {
    // Print the top bar
    for (int i = 0; i < frames.m_Capacity; ++i) {
        os << "-----";
    }
    os << "-\n";

    // Print the row of numbers

    for (int i = 0; i < frames.m_Capacity; ++i) {
        os << "|" << std::setw(4) << frames.m_pFrames[i].getPageID();
    }
    os << "|\n";

    // Print the bottom bar
    for (int i = 0; i < frames.m_Capacity; ++i) {
        os << "-----";
    }
    os << "-" << std::endl;

    return os;
}