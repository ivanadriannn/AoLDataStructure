// RED BLACK TREE 
// Nama : Ivan Adrian
// NIM : 2602076323
// Kelas : LB01

#include <stdio.h>
#include<string.h>
#include <stdlib.h>

enum Color{RED, BLACK};

struct Value{
	
    int value; 
    Value* parent; 
	Value* left;
	Value* right;
    enum Color redOrBlack;
    
};

void leftRotation(Value** root, Value* current){
	
    Value *childs = current->right; 
    current->right = childs->left;
    
    if(childs->left != NULL){
        childs->left->parent = current;
    }
    
    childs->parent = current->parent;
    
    if(current->parent == NULL){
        *root = childs;
    } 
	else if(current == current->parent->left){
        current->parent->left = childs;
    } 
	else{
        current->parent->right = childs;
    }
    
    childs->left = current;
    current->parent = childs;
}

void rightRotation(Value** root, Value*current){
	
    Value *childs = current->left;
    current->left = childs->right;
    
    if(childs->right != NULL){
        childs->right->parent = current;
    }
    
    childs->parent = current->parent;
    
    if(current->parent == NULL){
        *root = childs;
    } 
	else if(current == current->parent->right){
        current->parent->right = childs;
    } 
	else{
        current->parent->left = childs;
    }
    
    childs->right = current;
    current->parent = childs;
}

void violateRepairation(Value** root, Value* current){
	
    while(current->parent != NULL && current->parent->redOrBlack == RED){
        if(current->parent == current->parent->parent->left){
            Value* uncle = current->parent->parent->right;
            if(uncle != NULL && uncle->redOrBlack == RED){
                current->parent->redOrBlack = BLACK;
                uncle->redOrBlack = BLACK;
                current->parent->parent->redOrBlack = RED;
                current = current->parent->parent;
            } 
			else{
                if(current == current->parent->right){
                    current = current->parent;
                    leftRotation(root, current);
                }
                
                current->parent->redOrBlack = BLACK;
                current->parent->parent->redOrBlack = RED;
                rightRotation(root, current->parent->parent);
            }
        } 
		else{
            Value* uncle = current->parent->parent->left;
            if(uncle != NULL && uncle->redOrBlack == RED){
                current->parent->redOrBlack = BLACK;
                uncle->redOrBlack = BLACK;
                current->parent->parent->redOrBlack = RED;
                current = current->parent->parent;
            } 
			else{
                if(current == current->parent->left){
                    current = current->parent;
                    rightRotation(root, current);
                }
                
                current->parent->redOrBlack = BLACK;
                current->parent->parent->redOrBlack = RED;
                leftRotation(root, current->parent->parent);
            }
        }
    }
    
    (*root)->redOrBlack = BLACK;
}

void insertValue(Value** root, int value){
	
    Value *newItem = (Value*)malloc(sizeof(Value));
    
    newItem->value = value;
    newItem->parent = NULL;
	newItem->left = NULL;
	newItem->right = NULL;
    newItem->redOrBlack = RED; 
    
    Value* current = *root;
    Value* parent = NULL;
    
    while(current != NULL){
        parent = current;
        if(newItem->value < current->value){
            current = current->left;
        } 
		else{
            current = current->right;
        }
    }
    
    newItem->parent = parent;
    
    if(parent == NULL){
        *root = newItem;
    } 
	else if(newItem->value < parent->value){
        parent->left = newItem;
    } 
	else{
        parent->right = newItem;
    }
    
    violateRepairation(root, newItem);
}

void printInorder(Value *root){
	
	if (root == NULL){
		return;
	}
    else if(root != NULL){
        printInorder(root->left);
        printf("%d ", root->value);
        printInorder(root->right);
    }
    
}

int main() {
	Value *root = NULL;
	
    int value[] = {41, 22, 5, 51, 48, 29, 18, 21, 45, 3};
    int nValue = sizeof(value) / sizeof(value[0]);
	
	int i = 0;
	while(i < nValue){
        insertValue(&root, value[i]);
		i++;
	}

    puts("Inorder Traversal of Created Tree");
    printInorder(root);

    return 0;
}
