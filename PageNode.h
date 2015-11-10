//
// Created by William Lees on 11/9/15.
//

#ifndef PAGE_SELECTION_PAGENODE_H
#define PAGE_SELECTION_PAGENODE_H


class PageNode {
public:
    PageNode() {this->m_PageID = 0;}
    PageNode(int pageID);
    int getPageID();

    void setChild(PageNode *childNode);
    PageNode* getChild();

    void setLastCalled(int time);
    int getLastCalled();

private:
    // Pointer to child node
    PageNode   *m_pChild;
    int         m_LastCalled;
    int         m_PageID;

};


#endif //PAGE_SELECTION_PAGENODE_H
