#include <stdio.h>
#include <stdlib.h>

// Define the structure for an AVL Tree node
typedef struct AVLNode {
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

// Utility function to get the height of a node
int height(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Utility function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new AVL Tree node
AVLNode* createNode(int key) {
    AVLNode *node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // New node is initially at height 1
    return node;
}

// Right rotate utility function
AVLNode* rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotate utility function
AVLNode* leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get the balance factor of a node
int getBalance(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// Function to insert a key into the AVL Tree
AVLNode* insert(AVLNode* node, int key) {
    // Perform the normal BST insert
    if (node == NULL) {
        return createNode(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node; // Duplicate keys are not allowed
    }

    // Update the height of this ancestor node
    node->height = max(height(node->left), height(node->right)) + 1;

    // Get the balance factor of this ancestor node to check whether
    // this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Utility function to find the node with the minimum value
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Function to delete a key from the AVL Tree
AVLNode* deleteNode(AVLNode* root, int key) {
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == NULL) {
        return root;
    }

    // If the key to be deleted is smaller than the root's key, then it lies in the left subtree
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    // If the key to be deleted is greater than the root's key, then it lies in the right subtree
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    // If key is same as root's key, then this is the node to be deleted
    else {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else { // One child case
                *root = *temp; // Copy the contents of the non-empty child
            }
            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            AVLNode* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (root == NULL) {
        return root;
    }

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = max(height(root->left), height(root->right)) + 1;

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // Return the (unchanged) node pointer
    return root;
}

// Function to search a key in the AVL Tree
AVLNode* search(AVLNode* root, int key) {
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key == key) {
        return root;
    }

    // Key is greater than root's key
    if (root->key < key) {
        return search(root->right, key);
    }

    // Key is smaller than root's key
    return search(root->left, key);
}

// Function to print the AVL Tree (Inorder Traversal)
void inorder(AVLNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Main function to test AVL Tree operations
int main() {
    AVLNode* root = NULL;

    // Insert elements into the AVL Tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 5);

    // Print the AVL Tree
    printf("Inorder traversal of the AVL Tree:\n");
    inorder(root);
    printf("\n");

    // Search for an element
    int key = 15;
    AVLNode* result = search(root, key);
    if (result != NULL) {
        printf("Element %d found in the AVL Tree.\n", key);
    } else {
        printf("Element %d not found in the AVL Tree.\n", key);
    }

    // Delete an element
    key = 20;
    root = deleteNode(root, key);
    printf("Inorder traversal after deleting %d:\n", key);
    inorder(root);
    printf("\n");

    return 0;
}
