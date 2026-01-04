#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        return create_node(data);
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    
    return root;
}

bool search(Node* root, int data) {
    if (root == NULL) {
        return false;
    }
    
    if (root->data == data) {
        return true;
    }
    
    if (data < root->data) {
        return search(root->left, data);
    }
    return search(root->right, data);
}

Node* find_min(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* delete_node(Node* root, int data) {
    if (root == NULL) {
        return root;
    }
    
    if (data < root->data) {
        root->left = delete_node(root->left, data);
    } else if (data > root->data) {
        root->right = delete_node(root->right, data);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        
        Node* temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data);
    }
    
    return root;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void free_tree(Node* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main() {
    Node* root = NULL;
    
    int elements[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(elements) / sizeof(elements[0]);
    
    for (int i = 0; i < n; i++) {
        root = insert(root, elements[i]);
    }
    
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");
    
    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");
    
    printf("Postorder traversal: ");
    postorder(root);
    printf("\n");
    
    printf("\nSearch 40: %s\n", search(root, 40) ? "Found" : "Not found");
    printf("Search 100: %s\n", search(root, 100) ? "Found" : "Not found");
    
    root = delete_node(root, 30);
    printf("\nAfter deleting 30: ");
    inorder(root);
    printf("\n");
    
    free_tree(root);
    
    return 0;
}
