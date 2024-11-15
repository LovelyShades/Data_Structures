#include <stdio.h>
#include <stdlib.h>

// Definition of the TNode structure
typedef struct TNode {
    int data;
    struct TNode* pLeft;  // left child of this node
    struct TNode* pRight; // right child of this node
} TNode;

// Function to create a new node
TNode* createNode(int data) {
    TNode* newNode = (TNode*)malloc(sizeof(TNode));
    newNode->data = data;
    newNode->pLeft = NULL;
    newNode->pRight = NULL;
    return newNode;
}

/*
 * Precondition: A is a sorted array
 * This function creates and returns a balanced BST
 * containing the numbers in A[start] to A[end].
 */
TNode* createTreeRec(int *A, int start, int end) {
    /* Base case: If start index is greater than end, return NULL*/
    if (start > end) {
        return NULL;
    }
   
    /* Find the mid index*/
    int mid = start + (end - start) / 2; 
   
    /* Create a new node with mid */
    TNode* root = createNode(A[mid]);
   
    /* Recursively create the left and right subtrees */
    root->pLeft = createTreeRec(A, start, mid - 1);  
    root->pRight = createTreeRec(A, mid + 1, end);    
   
    return root; 
}


// Function to perform inorder traversal of the BST
void inorderTraversal(TNode* root) {
    if (root != NULL) {
        inorderTraversal(root->pLeft);
        printf("%d ", root->data);
        inorderTraversal(root->pRight);
    }
}

// Main function to test the BST creation
int main() {
    int A[] = {9, 10, 15, 30, 35, 42, 46, 50, 57, 61, 67, 72, 78, 80, 89};
    int n = sizeof(A) / sizeof(A[0]);

    // Create a balanced BST from the sorted array
    TNode* root = createTreeRec(A, 0, n - 1);

    // Perform inorder traversal to verify the tree structure
    printf("Inorder traversal of the balanced BST: ");
    inorderTraversal(root); // Should print the elements in sorted order

    return 0;
}
