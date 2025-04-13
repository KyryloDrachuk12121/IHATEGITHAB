#ifndef BST_H
#define BST_H

#include "node.h"

typedef Node* NodePtr;

NodePtr BSTPut(NodePtr, Key key, Value val);
Value BSTGet(NodePtr, Key key);

NodePtr BSTFloor(NodePtr, Key key);
NodePtr BSTCeiling(NodePtr, Key key);

int BSTRank(NodePtr, Key key);
int BSTSize(NodePtr);

NodePtr* BSTNodes(NodePtr head, int* arraySize);
void BSTIterate(NodePtr head, void (*func)(NodePtr));

NodePtr BSTDeleteMin(NodePtr root);
NodePtr BSTDelete(NodePtr, Key key);

Key BSTMin(NodePtr);
Key BSTMax(NodePtr);

NodePtr BSTDeleteMax(NodePtr root);
NodePtr BSTSelect(NodePtr root, int k);  // Added declaration

void BSTPrint(const NodePtr);
void BSTPrintReverse(const NodePtr);  // Added declaration

void BSTDestroy(NodePtr);

int BSTIsBalanced(NodePtr root);
int BSTHeight(NodePtr node);

#endif