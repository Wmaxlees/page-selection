//
// Created by William Lees on 11/9/15.
//

#ifndef PAGE_SELECTION_PAGENODE_H
#define PAGE_SELECTION_PAGENODE_H


class PageNode {
public:
    PageNode();
    PageNode(int pageID);
    int getPageID();

    void setChild(PageNode *childNode);
    PageNode* getChild();

    void setIndex(int index);
    int getIndex();

    void setLastCalled(int time);
    int getLastCalled();

private:
    // Pointer to child node
    PageNode   *m_pChild;
    int         m_LastCalled;
    int         m_PageID;
    int         m_Index;

};


#endif //PAGE_SELECTION_PAGENODE_H
