//
// Created by William Lees on 11/9/15.
//

#ifndef PAGE_SELECTION_PAGEARRAY_H
#define PAGE_SELECTION_PAGEARRAY_H

#include "PageNode.h"

class PageArray {
public:
    PageArray(int capacity);
    ~PageArray();

    void addPage(PageNode node);
    PageNode getNextPage();

    int getSize() { return this->m_Size; }

private:
    int         m_Size;
    int         m_Capacity;
    int         m_Current;

    PageNode   *m_pPages;
};


#endif //PAGE_SELECTION_PAGEARRAY_H
