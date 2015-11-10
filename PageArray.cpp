//
// Created by William Lees on 11/9/15.
//

#include "PageArray.h"

PageArray::PageArray(int capacity) {
    this->m_pPages = new PageNode[capacity];
    this->m_Capacity = capacity;
    this->m_Size = 0;
    this->m_Current = 0;
}

PageArray::~PageArray() {
    delete [] this->m_pPages;
}

void PageArray::reset() {
    this->m_Current = 0;
}

void PageArray::addPage(PageNode node) {
    if (this->m_Size < this->m_Capacity) {
        this->m_pPages[this->m_Size++] = node;
    }
}

PageNode PageArray::getNextPage() {
    if (this->m_Current < this->m_Capacity) {
        return this->m_pPages[this->m_Current++];
    }

    return PageNode(0);
}