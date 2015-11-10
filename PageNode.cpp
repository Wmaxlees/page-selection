//
// Created by William Lees on 11/9/15.
//

#include "PageNode.h"

PageNode::PageNode() {
    this->m_LastCalled = 0;
    this->m_PageID = 0;
}

PageNode::PageNode(int pageID) {
    this->m_LastCalled = 0;
    this->m_PageID = pageID;
}

int PageNode::getPageID() {
    return this->m_PageID;
}

void PageNode::setChild(PageNode *childNode) {
    this->m_pChild = childNode;
}

PageNode* PageNode::getChild() {
    return this->m_pChild;
}

void PageNode::setLastCalled(int time) {
    this->m_LastCalled = time;
}

int PageNode::getLastCalled() {
    return this->m_LastCalled;
}

void PageNode::setIndex(int index) {
    this->m_Index = index;
}

int PageNode::getIndex() {
    return this->m_Index;
}