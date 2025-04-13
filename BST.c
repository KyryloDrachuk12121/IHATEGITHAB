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
        return create_node(key, val);
    }
    if (less(key, head->key)) {
        head->left = BSTPut(head->left, key, val);
    } else if (greater(key, head->key)) {
        head->right = BSTPut(head->right, key, val);
    } else {
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
        arr[(*index)++] = head; // Store node instead of key
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

// Helper recursive function to delete the minimum key
NodePtr deleteMin(NodePtr head) {
    if (head->left == NULL) {
        NodePtr rightSubtree = head->right;
        free(head);          // Free memory of the deleted node
        return rightSubtree; // Return the right child
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

// Helper function to find the minimum node in a subtree 
NodePtr min(NodePtr head) {
    while (head->left != NULL) {
        head = head->left;
    }
    return head;
}

// Recursive function to delete a key from BST
NodePtr BSTDelete(NodePtr head, Key key) {
    if (head == NULL)
        return NULL; // Key not found

    if (less(key, head->key)) {
        head->left = BSTDelete(head->left, key);
    } else if (greater(key, head->key)) {
        head->right = BSTDelete(head->right, key);
    } else {
        // Node with only one child or no child
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

        // Node with two children: Get the inorder successor (smallest in right subtree)
        NodePtr temp = min(head->right);

        // Copy successor's key and value to this node
        head->key = temp->key;
        head->val = temp->val;

        // Delete the inorder successor
        head->right = deleteMin(head->right);
    }

    // Update count of nodes
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

void BSTDestroy(NodePtr head) {
    if (head == NULL)
        return;

    BSTDestroy(head->left);  // Free left subtree
    BSTDestroy(head->right); // Free right subtree
    free(head); // Free current node
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

int BSTIsBalanced(NodePtr root) {
    int height = 0;
    return BSTIsBalancedHelper(root, &height);
}
