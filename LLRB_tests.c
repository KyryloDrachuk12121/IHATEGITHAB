#include "LLRB.h"
#include "BST.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int calculateHeight(NodePtr node) {
    if (node == NULL) return 0;
    int leftHeight = calculateHeight(node->left);
    int rightHeight = calculateHeight(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int isBalancedHelper(NodePtr node, int* height) {
    if (node == NULL) {
        *height = 0;
        return 1;
    }
    int leftHeight = 0, rightHeight = 0;
    int leftBalanced = isBalancedHelper(node->left, &leftHeight);
    int rightBalanced = isBalancedHelper(node->right, &rightHeight);
    *height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    if (abs(leftHeight - rightHeight) > 1) return 0;
    return leftBalanced && rightBalanced;
}

int isBalanced(NodePtr root) {
    int height = 0;
    return isBalancedHelper(root, &height);
}

int checkBlackHeight(NodePtr node, int currentBlack, int* pathBlack) {
    if (node == NULL) {
        if (*pathBlack == -1) {
            *pathBlack = currentBlack;
            return 1;
        }
        return (currentBlack == *pathBlack);
    }
    int newBlack = currentBlack + (isRed(node) ? 0 : 1);
    return checkBlackHeight(node->left, newBlack, pathBlack) &&
        checkBlackHeight(node->right, newBlack, pathBlack);
}

int test_LLRBPropertiesHelper(NodePtr node) {
    if (node == NULL) return 1;
    if (isRed(node)) {
        if (node->left && isRed(node->left)) {
            printf("Violation: Two consecutive left red links at key %s\n", node->key);
            return 0;
        }
        if (node->right && isRed(node->right)) {
            printf("Violation: Right-leaning red link at key %s\n", node->key);
            return 0;
        }
    }
    int blackHeight = -1;
    if (!checkBlackHeight(node, 0, &blackHeight)) {
        printf("Violation: Different black heights at subtree rooted at %s\n", node->key);
        return 0;
    }
    return test_LLRBPropertiesHelper(node->left) &&
        test_LLRBPropertiesHelper(node->right);
}

int test_LLRBProperties(NodePtr root) {
    if (root == NULL) return 1;
    if (isRed(root)) {
        printf("Violation: Root is not black\n");
        return 0;
    }
    return test_LLRBPropertiesHelper(root);
}

void test_LLRBBalance() {
    printf("\nTesting BST vs LLRB balance...\n");

    printf("\n1. Ascending order insertion:\n");
    NodePtr bstRoot = NULL, llrbRoot = NULL;
    char* keys[] = { "A", "B", "C", "D", "E", "F", "G" };
    int numKeys = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < numKeys; i++) {
        bstRoot = BSTPut(bstRoot, keys[i], NULL);
        llrbRoot = LLRBPut(llrbRoot, keys[i], NULL);
    }

    printf("BST height: %d, isBalanced: %s\n", calculateHeight(bstRoot), isBalanced(bstRoot) ? "Yes" : "No");
    printf("LLRB height: %d, isBalanced: %s\n", calculateHeight(llrbRoot), isBalanced(llrbRoot) ? "Yes" : "No");

    BSTDestroy(bstRoot);
    BSTDestroy(llrbRoot);

    printf("\n2. Descending order insertion:\n");
    bstRoot = NULL;
    llrbRoot = NULL;

    for (int i = numKeys - 1; i >= 0; i--) {
        bstRoot = BSTPut(bstRoot, keys[i], NULL);
        llrbRoot = LLRBPut(llrbRoot, keys[i], NULL);
    }

    printf("BST height: %d, isBalanced: %s\n", calculateHeight(bstRoot), isBalanced(bstRoot) ? "Yes" : "No");
    printf("LLRB height: %d, isBalanced: %s\n", calculateHeight(llrbRoot), isBalanced(llrbRoot) ? "Yes" : "No");

    BSTDestroy(bstRoot);
    BSTDestroy(llrbRoot);
}

NodePtr buildMinHeightBST(char* keys[], int start, int end) {
    if (start > end) return NULL;
    int mid = (start + end) / 2;
    NodePtr root = createNode(keys[mid], NULL);
    root->left = buildMinHeightBST(keys, start, mid - 1);
    root->right = buildMinHeightBST(keys, mid + 1, end);
    root->count = 1 + BSTSize(root->left) + BSTSize(root->right);
    return root;
}

void testMinHeightBST() {
    printf("\nTesting minimal height BST creation...\n");
    char* sortedKeys[] = { "A", "B", "C", "D", "E", "F", "G" };
    int n = sizeof(sortedKeys) / sizeof(sortedKeys[0]);
    NodePtr root = buildMinHeightBST(sortedKeys, 0, n - 1);
    printf("In-order traversal: ");
    BSTIterate(root, printNode);
    printf("\n");
    printf("Tree height: %d\n", BSTHeight(root));
    printf("Is balanced: %s\n", isBalanced(root) ? "Yes" : "No");
    BSTDestroy(root);
}

void testBSTValidation() {
    printf("\nRunning BST validation tests...\n");

    NodePtr validBST = NULL;
    validBST = BSTPut(validBST, "D", NULL);
    validBST = BSTPut(validBST, "B", NULL);
    validBST = BSTPut(validBST, "F", NULL);
    validBST = BSTPut(validBST, "A", NULL);
    validBST = BSTPut(validBST, "C", NULL);
    validBST = BSTPut(validBST, "E", NULL);
    assert(isBST(validBST) == true);
    printf("Test 1 (Valid BST) passed.\n");

    NodePtr invalidBST = createNode("D", NULL);
    invalidBST->left = createNode("B", NULL);
    invalidBST->right = createNode("A", NULL);
    assert(isBST(invalidBST) == false);
    printf("Test 2 (Invalid BST - right child) passed.\n");

    NodePtr invalidBST2 = createNode("D", NULL);
    invalidBST2->left = createNode("E", NULL);
    invalidBST2->right = createNode("F", NULL);
    assert(isBST(invalidBST2) == false);
    printf("Test 3 (Invalid BST - left child) passed.\n");

    NodePtr singleNode = createNode("A", NULL);
    assert(isBST(singleNode) == true);
    printf("Test 4 (Single node) passed.\n");

    assert(isBST(NULL) == true);
    printf("Test 5 (Empty tree) passed.\n");

    BSTDestroy(validBST);
    BSTDestroy(invalidBST);
    BSTDestroy(invalidBST2);
    BSTDestroy(singleNode);

    printf("All BST validation tests passed!\n");
}

int main() {
    NodePtr root = NULL;
    char* testKeys[] = { "S", "E", "A", "R", "C", "H", "X", "M", "P", "L" };
    int numKeys = sizeof(testKeys) / sizeof(testKeys[0]);

    for (int i = 0; i < numKeys; i++) {
        root = LLRBPut(root, testKeys[i], NULL);
    }

    printf("Testing LLRB properties...\n");
    if (test_LLRBProperties(root)) {
        printf("All LLRB properties are satisfied!\n");
    }

    printf("LLRB tree in-order: ");
    BSTIterate(root, printNode);
    printf("\n");

    test_LLRBBalance();
    testBSTValidation();
    testMinHeightBST();
    BSTDestroy(root);
    return 0;
}
