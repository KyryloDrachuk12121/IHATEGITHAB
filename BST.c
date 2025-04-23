#include "BST.h"
#include "node.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Value BSTGet(NodePtr head, Key key) {
    NodePtr x = head;
    while (x != NULL) {
        if (less(key, x->key)) {
            x = x->left;
        } else if (greater(key, x->key)) {
            x = x->right;
        } else {
            return x->val;
        }
    }
    return NULL;
}

NodePtr BSTPut(NodePtr head, Key key, Value val) {
    if (head == NULL) {
        return createNode(key, val);
    }
    if (less(key, head->key)) {
        head->left = BSTPut(head->left, key, val);
    }
    else if (greater(key, head->key)) {
        head->right = BSTPut(head->right, key, val);
    }
    else {
        head->val = val;
    }
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

NodePtr BSTFloor(NodePtr head, Key key) {
    if (head == NULL) {
        return NULL;
    }
    
    if (equal(key, head->key)) {
        return head;
    }
    if (less(key, head->key)) {
        return BSTFloor(head->left, key);
    }
    NodePtr t = BSTFloor(head->right, key);
    return (t != NULL) ? t : head;
}

int BSTSize(NodePtr head) { return (head != NULL) ? head->count : 0; }

void inorderNodes(NodePtr head, NodePtr *arr, int *index) {
    if (head != NULL) {
        inorderNodes(head->left, arr, index);
        arr[(*index)++] = head;
        inorderNodes(head->right, arr, index);
    }
}

NodePtr *BSTNodes(NodePtr head, int *arraySize) {
    if (head == NULL) {
        *arraySize = 0;
        return NULL;
    }

    *arraySize = head->count;
    NodePtr *nodesArray = (NodePtr*)malloc((*arraySize) * sizeof(NodePtr));
    if (!nodesArray) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    int size = 0;
    inorderNodes(head, nodesArray, &size);
    return nodesArray;
}

NodePtr deleteMin(NodePtr head) {
    if (head->left == NULL) {
        NodePtr rightSubtree = head->right;
        free(head);       
        return rightSubtree; 
    }

    head->left = deleteMin(head->left);
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

NodePtr BSTDeleteMin(NodePtr head) {
    if (head == NULL)
        return NULL;
    
    return deleteMin(head);
}

NodePtr min(NodePtr head) {
    while (head->left != NULL) {
        head = head->left;
    }
    return head;
}

NodePtr BSTDelete(NodePtr head, Key key) {
    if (head == NULL)
        return NULL; 

    if (less(key, head->key)) {
        head->left = BSTDelete(head->left, key);
    } else if (greater(key, head->key)) {
        head->right = BSTDelete(head->right, key);
    } else {

        if (head->right == NULL) {
            NodePtr leftSubtree = head->left;
            free(head);
            return leftSubtree;
        }
        if (head->left == NULL) {
            NodePtr rightSubtree = head->right;
            free(head);
            return rightSubtree;
        }

        NodePtr temp = min(head->right);


        head->key = temp->key;
        head->val = temp->val;

        head->right = deleteMin(head->right);
    }

    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

void BSTDestroy(NodePtr head) {
    if (head == NULL)
        return;

    BSTDestroy(head->left);  
    BSTDestroy(head->right); 
    free(head); 
}

void BSTIterate(NodePtr head, void (*func)(NodePtr)) {
    if (head == NULL)
        return;

    BSTIterate(head->left, func);
    func(head);
    BSTIterate(head->right, func);
}

NodePtr BSTCeiling(NodePtr head, Key key) {
    if (head == NULL) {
        return NULL;
    }

    if (equal(key, head->key)) {
        return head;
    }
    if (greater(key, head->key)) {
        return BSTCeiling(head->right, key);
    }
    NodePtr t = BSTCeiling(head->left, key);
    return (t != NULL) ? t : head;
}

int BSTRank(NodePtr head, Key key) {
    if (head == NULL) {
        return 0;
    }

    if (less(head->key, key)) {
        return BSTSize(head->left) + 1 + BSTRank(head->right, key);
    }
    return BSTRank(head->left, key);
}
NodePtr BSTSelect(NodePtr head, int k) {
    if (head == NULL) {
        return NULL;
    }

    int leftSize = BSTSize(head->left);
    if (leftSize > k) {
        return BSTSelect(head->left, k);
    }
    else if (leftSize < k) {
        return BSTSelect(head->right, k - leftSize - 1);
    }
    else {
        return head;
    }
}

Key BSTMin(NodePtr head) {
    if (head == NULL) {
        return NULL;
    }
    while (head->left != NULL) {
        head = head->left;
    }
    return head->key;
}

Key BSTMax(NodePtr head) {
    if (head == NULL) {
        return NULL;
    }
    while (head->right != NULL) {
        head = head->right;
    }
    return head->key;
}

NodePtr BSTDeleteMax(NodePtr head) {
    if (head == NULL) {
        return NULL;
    }
    if (head->right == NULL) {
        NodePtr leftSubtree = head->left;
        free(head);
        return leftSubtree;
    }
    head->right = BSTDeleteMax(head->right);
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

void BSTPrintReverse(const NodePtr head) {
    if (head == NULL) {
        return;
    }
    BSTPrintReverse(head->right);
    printf("%s ", head->key);
    BSTPrintReverse(head->left);
}
int BSTHeight(NodePtr node) {
    if (node == NULL) {
        return 0;
    }
    int leftHeight = BSTHeight(node->left);
    int rightHeight = BSTHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int BSTIsBalancedHelper(NodePtr node, int* height) {
    if (node == NULL) {
        *height = 0;
        return 1;
    }

    int leftHeight = 0, rightHeight = 0;
    int leftBalanced = BSTIsBalancedHelper(node->left, &leftHeight);
    int rightBalanced = BSTIsBalancedHelper(node->right, &rightHeight);

    *height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;

    if (abs(leftHeight - rightHeight) > 1) {
        return 0;
    }

    return leftBalanced && rightBalanced;
}
bool isBSTHelper(NodePtr node, const char* min, const char* max) {
    if (node == NULL) return true;

    if ((min != NULL && strcmp(node->key, min) <= 0) ||
        (max != NULL && strcmp(node->key, max) >= 0))
        return false;

    return isBSTHelper(node->left, min, node->key) &&
        isBSTHelper(node->right, node->key, max);
}

bool isBST(NodePtr root) {
    return isBSTHelper(root, NULL, NULL);
}
