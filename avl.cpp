#include <iostream>
#include <queue>
using namespace std;


int max(int a, int b) {
    return (a > b) ? a : b;
    
}

// AVLNode structure represents each node in the AVL tree
struct AVLNode {
    // AVL data model
    int key;
    int height;
    AVLNode* left;
    AVLNode* right;
    // Traditional constructor
   AVLNode(int k) {
       key = k;
       height = 1;
       left = nullptr;
       right = nullptr;
   }
};

// Get the height of a node (returns 0 if node is null)
int height(AVLNode* n) {
   return n ? n->height : 0;
}

// Calculate balance factor: height(left subtree) - height(right subtree)
// Balance factor should be -1, 0, or 1 for a balanced AVL tree
int getBalance(AVLNode* n) {
   return n ? height(n->left) - height(n->right) : 0;
}

// Update the height of a node based on its children's heights
void updateHeight(AVLNode* n) {
   if(n) {
    n->height = 1 + max(height(n->left), height(n->right));
 }
}

// Right Rotation
// Used when left subtree is heavier (Left-Left case)
AVLNode* rotateRight(AVLNode* y) {
   AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    // Perform rotation
   x->right = y;
    y->left = T2;
    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;  // New root of this subtree
}

// Left Rotation
// Used when right subtree is heavier (Right-Right case)
AVLNode* rotateLeft(AVLNode* x) {
   
    
    // Perform rotation
   
    
    // Update heights
    
    
    return y;  // New root of this subtree
}

// Insert a new key into the AVL tree
// Returns the new root of the subtree
AVLNode* insert(AVLNode* node, int key) {
    // 1. Perform standard BST insertion
    if(!node) {
      return new AVLNode(key);
}
     if(key < node->key) {
       node->left = insert(node->left, key);
}   else if(key > node->key) {
        node->right = insert(node->right, key);
}    else {
       return node;
}
    // 2. Update height of this ancestor node
      updateHeight(node);
    // 3. Get the balance factor to check if this node became unbalanced
   int balance = getBalance(node);
   
   
    // 4. If unbalanced, there are 4 cases:
    
    // Left Left Case: Right rotation needed
   
    
    // Right Right Case: Left rotation needed
    
    
    
    // Left Right Case: Left rotation on left child, then right rotation
    
    
    // Right Left Case: Right rotation on right child, then left rotation
    
    
    // Return the (unchanged) node pointer
   
}

// Find the node with minimum key value (leftmost node)
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left) {
        current = current->left;
    }
    return current;
}

// Delete a node with given key from the AVL tree
// Returns the new root of the subtree
AVLNode* deleteNode(AVLNode* node, int key) {
    // 1. Perform standard BST delete
    if (!node) {
        return node;
    }
    
    if (key < node->key) {
        node->left = deleteNode(node->left, key);
    } else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    } else {
        // Node with only one child or no child
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                // No child case
                temp = node;
                node = NULL;
            } else {
                // One child case: copy the contents
                *node = *temp;
            }
            delete temp;
        } else {
            // Node with two children: Get inorder successor (smallest in right subtree)
            AVLNode* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
    }
     
    // If tree had only one node, return
    if (!node) {
        return node;
    }
    
    // 2. Update height of current node
    updateHeight(node);
    
    // 3. Get balance factor to check if this node became unbalanced
    int balance = getBalance(node);
    
    // 4. If unbalanced, there are 4 cases:
    
    // Left Left Case
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }
    
    // Left Right Case
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    // Right Right Case
    if (balance < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }
    
    // Right Left Case
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    
    return node;
}

// Inorder traversal: Left -> Root -> Right
// Produces sorted output for BST
void inorder(AVLNode* node) {
    if (node) {
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }
}

// Preorder traversal: Root -> Left -> Right
void preorder(AVLNode* node) {
    if (node) {
        cout << node->key << " ";
        preorder(node->left);
        preorder(node->right);
    }
}

// Postorder traversal: Left -> Right -> Root
// Useful for deleting tree (delete children before parent)
void postorder(AVLNode* node) {
    if (node) {
        postorder(node->left);
        postorder(node->right);
        cout << node->key << " ";
    }
}

// Level-order traversal: Visit nodes level by level (Breadth-First Search)
// Uses a queue to process nodes in order of their depth
void levelorder(AVLNode* root) {
    if (!root) {
        return;
    }
    
    queue<AVLNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        AVLNode* current = q.front();
        q.pop();
        
        cout << current->key << " ";
        
        // Enqueue left child
        if (current->left) {
            q.push(current->left);
        }
        
        // Enqueue right child
        if (current->right) {
            q.push(current->right);
        }
    }
}

// Search for a key in the tree
// Returns true if found, false otherwise
bool search(AVLNode* node, int key) {
    if (!node) {
        return false;
    }
    if (key == node->key) {
        return true;
    }
    if (key < node->key) {
        return search(node->left, key);
    }
    return search(node->right, key);
}

// Display tree in inorder (sorted)
void displayInorder(AVLNode* root) {
    cout << "Inorder: ";
    inorder(root);
    cout << endl;
}

// Display tree in preorder
void displayPreorder(AVLNode* root) {
    cout << "Preorder: ";
    preorder(root);
    cout << endl;
}

// Display tree in postorder
void displayPostorder(AVLNode* root) {
    cout << "Postorder: ";
    postorder(root);
    cout << endl;
}

// Display tree in level-order
void displayLevelorder(AVLNode* root) {
    cout << "Level-order: ";
    levelorder(root);
    cout << endl;
}

// Main function demonstrating AVL tree operations
int main() {
    AVLNode* root = NULL;  // Initialize empty tree
    
    // Insert nodes into the AVL tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);
    
    // Display the tree after insertions
    cout << "After insertions:" << endl;
    displayInorder(root);
    displayPreorder(root);
    displayPostorder(root);
    displayLevelorder(root);
    cout << "Height: " << height(root) << endl;
    
    // Search for specific keys
    cout << "\nSearch 25: " << (search(root, 25) ? "Found" : "Not found") << endl;
    cout << "Search 35: " << (search(root, 35) ? "Found" : "Not found") << endl;
    
    // Delete a node
    root = deleteNode(root, 40);
    cout << "\nAfter deleting 40:" << endl;
    displayInorder(root);
    displayPreorder(root);
    displayPostorder(root);
    displayLevelorder(root);
    cout << "Height: " << height(root) << endl;
    
    return 0;
}
