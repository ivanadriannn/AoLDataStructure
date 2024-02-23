// RED BLACK TREE 
// Nama : Ivan Adrian
// NIM : 2602076323
// Kelas : LB01

#include <stdio.h>
#include<string.h>
#include <stdlib.h>

enum Color{RED, BLACK};
// mendefinisikan dua warna RED atau BLACK

struct Value{
	
    int value; 
	// menyimpan nilai dari simpul
    Value* parent; 
	// menunjuk ke simpul induk dari simpul saat ini
	Value* left;
	// menunjuk ke simpul anak kiri dari simpul saat ini
	Value* right;
	// menunjuk ke simpul anak kanan dari simpul saat ini
    enum Color redOrBlack;
    // menyimpan informasi mengenai warna simpul
    
};

void leftRotation(Value** root, Value* current){
	// melakukan rotasi ke kiri pada sebuah node
	
    Value *childs = current->right; 
    // childs merupakan simpul baru setelah rotasi
    current->right = childs->left;
    // mengubah anak kanan dari simpul current menjadi anak kiri dari simpul childs
    
    if(childs->left != NULL){
	// jika anak kiri dari childs bukan NULL
        childs->left->parent = current;
        // mengubah pointer parent dari anak kiri tersebut menjadi simpul current
    }
    
    childs->parent = current->parent;
    // mengubah pointer parent dari childs menjadi pointer parent dari simpul current
    
    if(current->parent == NULL){
    // jika simpul current adalah akar (tidak memiliki parent)
        *root = childs;
        // maka simpul childs menjadi akar baru
    } 
	else if(current == current->parent->left){
	// jika simpul current adalah simpul kiri dari simpul parentnya
        current->parent->left = childs;
        // mengubah pointer anak kiri dari parent simpul current menjadi childs
    } 
	else{
	// jika simpul current adalah simpul kanan dari simpul parentnya
        current->parent->right = childs;
        // mengubah pointer anak kanan dari parent simpul current menjadi childs
    }
    
    childs->left = current;
    // mengubah pointer anak kiri dari childs menjadi simpul current
    current->parent = childs;
    // mengubah pointer parent dari simpul current menjadi childs
}

void rightRotation(Value** root, Value*current){
	// melakukan rotasi ke kanan pada sebuah node
	
    Value *childs = current->left;
    // childs merupakan simpul baru setelah rotasi
    current->left = childs->right;
    // mengubah anak kiri dari simpul current menjadi anak kanan dari simpul childs
    
    if(childs->right != NULL){
    // jika anak kanan dari childs bukan NULL
        childs->right->parent = current;
        // mengubah pointer parent dari anak kanan tersebut menjadi simpul current
    }
    
    childs->parent = current->parent;
    // mengubah pointer parent dari childs menjadi pointer parent dari simpul current
    
    if(current->parent == NULL){
    // jika simpul current adalah akar (tidak memiliki parent)
        *root = childs;
        // maka simpul childs menjadi akar baru
    } 
	else if(current == current->parent->right){
	// jika simpul current adalah simpul kanan dari simpul parentnya
        current->parent->right = childs;
        // mengubah pointer anak kanan dari parent simpul current menjadi childs
    } 
	else{
	// jika simpul current adalah simpul kiri dari simpul parentnya
        current->parent->left = childs;
        // mengubah pointer anak kiri dari parent simpul current menjadi childs
    }
    
    childs->right = current;
    // mengubah pointer anak kanan dari childs menjadi simpul current
    current->parent = childs;
    // mengubah pointer parent dari simpul current menjadi childs
}

void violateRepairation(Value** root, Value* current){
	// memperbaiki pelanggaran aturan pada struktur RED BLACK TREE,
	// setelah melalukan operasi penyisipan yang mungkin menyebabkan pelanggaran
	
    while(current->parent != NULL && current->parent->redOrBlack == RED){
    // selama simpul current memiliki parent dan parentnya memiliki warna RED
	// berarti masih ada pelanggaran sifat-sifat Red-Black Tree yang perlu dibenahi
        if(current->parent == current->parent->parent->left){
        // memeriksa apakah parent adalah left child dari grandParent
            Value* uncle = current->parent->parent->right;
            // mendeklrasikan pointer uncle yang menunjuk ke right child dari grandParent
            if(uncle != NULL && uncle->redOrBlack == RED){
            // memerika apakah uncle tidak kosong dan berwarna merah
                current->parent->redOrBlack = BLACK;
                // mengubah warna parent menjadi BLACK
                uncle->redOrBlack = BLACK;
                // mengubah warna uncle menjadi BLACK
                current->parent->parent->redOrBlack = RED;
                // mengubah warna grandParent menjadi RED
                current = current->parent->parent;
                // menetapkan current menjadi grandParent untuk melanjutkan perbaikan lebih lanjut
            } 
			else{
			// jika kondisi di atas tidak terpenuhi
			// artinya masih terjadi pelanggaran
                if(current == current->parent->right){
            	// jika current adalah right child dari parent
                    current = current->parent;
                    // menetapkan current menjadi parent
                    leftRotation(root, current);
                    // melakukan rotasi ke kiri pada simpul parent
                }
                
                current->parent->redOrBlack = BLACK;
                // mengubah warna simpul parent menjadi BLACK
                current->parent->parent->redOrBlack = RED;
                // mengubah warna simpul grandParent menjadi RED
                rightRotation(root, current->parent->parent);
                // melakukan rotasi ke kanan pada simpul grandParent
            }
        } 
		else{
		// jika kondisi di atas tidak terpenuhi
		// artinya masih terjadi pelanggaran
            Value* uncle = current->parent->parent->left;
            // mendeklrasikan pointer uncle yang menunjuk ke left child dari grandParent
            if(uncle != NULL && uncle->redOrBlack == RED){
            // memerika apakah uncle tidak kosong dan berwarna merah	
                current->parent->redOrBlack = BLACK;
                // mengubah warna parent menjadi BLACK
                uncle->redOrBlack = BLACK;
                // mengubah warna uncle menjadi BLACK
                current->parent->parent->redOrBlack = RED;
                // mengubah warna grandParent menjadi RED
                current = current->parent->parent;
                // menetapkan current menjadi grandParent untuk melanjutkan perbaikan lebih lanjut
            } 
			else{
			// jika kondisi di atas tidak terpenuhi
			// artinya masih terjadi pelanggaran
                if(current == current->parent->left){
                // jika current adalah left child dari parent
                    current = current->parent;
                    // menetapkan current menjadi parent
                    rightRotation(root, current);
                    // melakukan rotasi ke kanan pada simpul parent
                }
                
                current->parent->redOrBlack = BLACK;
                // mengubah warna simpul parent menjadi BLACK
                current->parent->parent->redOrBlack = RED;
                // mengubah warna simpul grandParent menjadi RED
                leftRotation(root, current->parent->parent);
                // melakukan rotasi ke kiri pada simpul grandParent
            }
        }
    }
    
    (*root)->redOrBlack = BLACK;
    // setelah perbaikan selesai dilakukan,
    // warna root diubah kembali menjadi BLACK
    // untuk memastikan bahwa properti Red-Black Tree Tetap terjaga
}

void insertValue(Value** root, int value){
	// fungsi untuk menyisipkan nilai baru ke dalam RBT
	
    Value *newItem = (Value*)malloc(sizeof(Value));
    // mengalokasikan memori yang diperlukan
    
    newItem->value = value;
    // menetapkan nilai value simpul baru sesuai dengan nilai yang ditentukan
    newItem->parent = NULL;
    // mengatur parent menjadi NULL
	newItem->left = NULL;
	// mengatur left child menjadi NULL
	newItem->right = NULL;
	// mengatur right child menjadi NULL
    newItem->redOrBlack = RED; 
    // mengatur warna simpul baru menjadi RED sesuai aturan RBT
    
    Value* current = *root;
    // mengatur pointer current sebagai root
    Value* parent = NULL;
    // mengatur pointer parent menjadi NULL
    
    while(current != NULL){
    // memulai loop while untuk mencari posisi yang tepat untuk menyisipkan simpul baru
    // loop ini berjalan selama current tidak NULL.
        parent = current;
        // setiap kali melangkah ke simpul selanjutnya
        // menyimpan simpul saat ini dalam parent
        if(newItem->value < current->value){
        // jika newItem->value lebih kecil dari nilai simpul saat ini
            current = current->left;
            // maka simpul berikutnya yang akan dijelajahi adalah anak kiri dari simpul saat ini
        } 
		else{
		// jika tidak,
            current = current->right;
            // simpul berikutnya adalah anak kanan
        }
    }
    
    newItem->parent = parent;
    // setelah mencapai posisi yang tepat untuk menyisipkan simpul baru
	// mengatur pointer parent dari simpul baru 
	// sebagai simpul parent yang terakhir disimpan.
    
    if(parent == NULL){
    // jika parent NULL
        *root = newItem;
        // berarti simpul baru adalah simpul pertama dalam pohon
        // dalam hal ini, mengatur root yang ditunjuk oleh pointer root ke simpul baru
    } 
	else if(newItem->value < parent->value){
	// jika newItem->value lebih kecil dari nilai simpul parent->value
        parent->left = newItem;
        // mengatur simpul baru sebagai anak kiri dari parent
    } 
	else{
	// Jika tidak, 
        parent->right = newItem;
        // mengatur simpul baru sebagai anak kanan dari simpul parent
    }
    
    violateRepairation(root, newItem);
    // setelah simpul baru disisipkan ke dalam pohon
    // melalakukan perbaikan 
    // untuk memastikan bahwa sifat-sifat Red-Black Tree tetap terjaga
}

void printInorder(Value *root){
	// mencetak nilai dari setiap node dalam struktur tree secara inorder
	
	if (root == NULL){
	// memerika apakah item adalah NULL
	// yaitu jika mencapai lead atau mencetak subtree kosong
		return;
		// jika ya, maka fungsi akan mengembalikan (base case) dan keluar dari rekursi
	}
    else if(root != NULL){
    // jika item tidak NULL
        printInorder(root->left);
        // memanggil rekursif fungsi printInorder untuk mencetak subtree kiri dari root
        printf("%d ", root->value);
        // mencetak nilai dari root saat ini
        printInorder(root->right);
        // memanggil rekursif fungsi printInorder untuk mencetak subtree kanan dari root
    }
    
}

int main() {
	Value *root = NULL; 
	// inisialisasi root sebagai NULL
	
    int value[] = {41, 22, 5, 51, 48, 29, 18, 21, 45, 3};
    // mendefinisikan sebuah array value yang berisi beberapa nilai
    int nValue = sizeof(value) / sizeof(value[0]);
    // penghitungan jumlah elemen dalam array menggunakan sizeof agar lebih dinamis
	
	int i = 0;
	while(i < nValue){
	// perulangan while untuk memasukkan setiap nilai dari array
        insertValue(&root, value[i]);
		i++;
	}

    puts("Inorder Traversal of Created Tree");
    printInorder(root);
    // pencetakan hasil penelusuran inorder (inorder traversal) dari tree yang telah dibuat

    return 0;
}
