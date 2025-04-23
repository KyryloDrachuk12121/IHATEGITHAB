#include "BST.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_node(NodePtr node) {
    if (node) {
        printf("%s ", node->key);
    }
}

int main() {
    NodePtr head = createNode("S", "value for key S");
    BSTPut(head, "E", "some value");
    BSTPut(head, "X", NULL);
    BSTPut(head, "A", NULL);
    BSTPut(head, "R", NULL);
    BSTPut(head, "C", NULL);
    BSTPut(head, "H", NULL);
    BSTPut(head, "M", NULL);

    printf("Value of key 'E': '%s'\n", (char*)BSTGet(head, "E"));

    NodePtr floorNode = BSTFloor(head, "G");
    if (floorNode) {
        printf("Floor of 'G': %s\n", floorNode->key);
    }

    printf("Rank of 'R': %d\n", BSTRank(head, "R"));
    printf("Size of BST: %d\n", BSTSize(head));

    int arraySize;
    NodePtr* nodes = BSTNodes(head, &arraySize);
    printf("All nodes in sorted order: ");
    for (int i = 0; i < arraySize; i++) {
        printf("%s ", nodes[i]->key);
    }
    free(nodes);
    printf("\n");

    printf("In-order traversal: ");
    BSTIterate(head, print_node);
    printf("\n");

    printf("Minimum key: %s\n", BSTMin(head));
    printf("Maximum key: %s\n", BSTMax(head));

    head = BSTDeleteMin(head);
    printf("BST after deleting min: ");
    BSTIterate(head, print_node);
    printf("\n");

    head = BSTDelete(head, "E");
    printf("BST after deleting 'E': ");
    BSTIterate(head, print_node);
    printf("\n");

    head = BSTDeleteMax(head);
    printf("BST after deleting max: ");
    BSTIterate(head, print_node);
    printf("\n");

    NodePtr ceilingNode = BSTCeiling(head, "G");
    if (ceilingNode) {
        printf("Ceiling of 'G': %s\n", ceilingNode->key);
    }

    NodePtr selectNode = BSTSelect(head, 2);
    if (selectNode) {
        printf("Element at rank 2: %s\n", selectNode->key);
    }

    printf("BST in reverse order: ");
    BSTPrintReverse(head);
    printf("\n");

    // Moved BST validation BEFORE destruction
    printf("\nChecking BST validity:\n");
    if (isBST(head)) {
        printf("The tree is a valid BST\n");
    }
    else {
        printf("The tree is NOT a valid BST\n");
    }

    BSTDestroy(head);

    return 0;
}
