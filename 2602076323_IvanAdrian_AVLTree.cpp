// AVL TREE
// Nama : Ivan Adrian
// NIM : 2602076323
// Kelas : LB01

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

struct Value{
	
    int value;
    int height;
    int balanceFactor;
    
    Value* left;
    Value* right;
    
};

Value* createNode(int value){ 
	
    Value* newValue = (Value*) malloc(sizeof(Value)); 
    newValue->value = value; 
    newValue->right = newValue->left = NULL; 
    newValue->height = 1; 
    
    return newValue; 
    
}

int max(int getHeightLeft, int getHeightRight){ 
	
    if(getHeightLeft > getHeightRight){ 
        return getHeightLeft; 
    }
    
    return getHeightRight; 
    
}

int getHeight(Value* current){ 
	
    if(current == NULL){
        return 0; 
    }
    
    return current->height; 
    
}

int setBalanceFactor(Value* current){ 

    if(current == NULL){
        return 0; 
    }
    
    return getHeight(current->left) - getHeight(current->right);
}

int setHeight(Value* current){ 
	
    if(current == NULL){
        return 0; 
    }
    
    return max(getHeight(current->left), getHeight(current->right)) + 1;
    
}

Value* updateNode(Value* current){ 
	
    if(current == NULL){
        return current;  
    }
    
    current->height = setHeight(current); 
    current->balanceFactor = setBalanceFactor(current);
    
    return current; 
    
}

Value* leftRotation(Value* current){
    
    Value *pivot = current->right;
    Value *childLeft = pivot->left;
    pivot->left = current;
    current->right = childLeft;
    current = updateNode(current);
    pivot = updateNode(pivot);
    
    return pivot;
}

Value* rightRotation(Value* current){
    
    Value *pivot = current->left;
    Value *childRight = pivot->right;
    pivot->right = current;
    current->left = childRight;
    current = updateNode(current);
    pivot = updateNode(pivot);
    
    return pivot;
}

Value* rotation(Value* current){

    if(current == NULL){
        return current;
    }

    // LL (Left-Left Case)
    if(current->balanceFactor > 1 && current->left->balanceFactor >= 0){
        return rightRotation(current);
    }

    // RR (Right-Right Case)
    else if(current->balanceFactor < -1 && current->right->balanceFactor <= 0){
        return leftRotation(current);
    }

    // LR (Left-Right Case)
    else if(current->balanceFactor > 1 && current->left->balanceFactor < 0){
        current->left = leftRotation(current->left);
        return rightRotation(current);
    }

    // RL (Right-Left Case)
    else if(current->balanceFactor < -1 && current->right->balanceFactor > 0){
        current->right = rightRotation(current->right);
        return leftRotation(current);
    }

    return current;
    
}

Value* insertValue(Value* root, int value){

    if(root == NULL){
        return createNode(value);
    }
	else if(value < root->value){
        root->left = insertValue(root->left, value);
    }
	else if(value > root->value){
        root->right = insertValue(root->right, value);
    }

    return rotation(updateNode(root));
    
}

Value* searchValue(Value* root, int value){
	
    if(root == NULL || root->value == value){
        return root;
    }
    else if(value < root->value){
        return searchValue(root->left, value);
    }
    else{
        return searchValue(root->right, value);
    }
    
}

Value* deleteValue(Value* root, int deletedValue){
	
    if(root == NULL){
        return root;
    }
    else if(deletedValue < root->value){
        root->left = deleteValue(root->left, deletedValue);
    }
    else if(deletedValue > root->value){
        root->right = deleteValue(root->right, deletedValue);
    }
    else if(deletedValue == root->value) {
        if(root->left == NULL && root->right == NULL){
            // Node to delete has no children
            free(root);
            root = NULL;
        }
        else if(root->left != NULL && root->right == NULL){
            // Node to delete has only left child
            Value *temp = root->left;
            free(root);
            root = temp;
        }
        else if(root->left == NULL && root->right != NULL){
            // Node to delete has only right child
            Value *temp = root->right;
            free(root);
            root = temp;
        }
        else if(root->left != NULL && root->right != NULL){
            // Node to delete has both left and right children
            Value *temp = root->left;
            while (temp->right) {
                temp = temp->right;
            }
            root->value = temp->value;
            root->left = deleteValue(root->left, temp->value);
        }
    }
    
    return rotation(updateNode(root));
    
}

void preOrder(Value* root){

    if(root){
        printf("%d ", root->value);  
        preOrder(root->left);  
        preOrder(root->right); 
    }
    
}

void inOrder(Value* root){

    if(root){
        inOrder(root->left);  
        printf("%d ", root->value);  
        inOrder(root->right);  
    }
    
}

void postOrder(Value* root){

    if(root){
        postOrder(root->left);  
        postOrder(root->right);  
        printf("%d ", root->value);  
    }
    
}

void printTraversal(Value* root){
	
	printf("Preorder: ");
    preOrder(root);  
    puts("");
    printf("Inorder: ");
    inOrder(root);  
    puts("");
    printf("Postorder: ");
    postOrder(root);  
    puts("");
    
}

void exitScreen(){
	
    system("cls");  
    puts("Thank You");  
    printf("Press Enter to exit");  
    getchar();  
    exit(0);  
    
}

void menuList(){
	
    int inputNumber;
    Value *root = NULL;

    do{
    	system("cls");
        puts("1. Insertion");  
        puts("2. Deletion");  
        puts("3. Traversal");  
        puts("4. Exit");  
        printf("Choose: ");  

        scanf("%d", &inputNumber); 
        getchar();  

        int valueToInput;
        int valueToDelete;

        switch(inputNumber){
            case 1:
                printf("Insert: "); 
                scanf("%d", &valueToInput);  
                getchar();  
                root = insertValue(root, valueToInput);  
                printf("Value %d was inserted\n", valueToInput);
                break;
            case 2:
                printf("Delete: "); 
                scanf("%d", &valueToDelete);  
                getchar();  
                
                if(searchValue(root, valueToDelete) != NULL){
                    root = deleteValue(root, valueToDelete);  
                    puts("Data Found");
                    printf("Value %d was deleted\n", valueToDelete);  
                } 
                else if(searchValue(root, valueToDelete) == NULL){
                    puts("Data not found");  
                }
                root = deleteValue(root, valueToDelete); 
				 
                break;
            case 3:
                printTraversal(root);
                break;
            case 4:
                exitScreen();  
                break;
        }
        puts("Press enter to continue...");
        getchar();
    }while(inputNumber >= 1 && inputNumber <= 4); 
    
}

int main(){
	
    menuList(); 
    return 0;
    
}
