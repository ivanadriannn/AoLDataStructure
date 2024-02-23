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
	// Membuat simpul baru dengan nilai yang ditentukan
	
    Value* newValue = (Value*) malloc(sizeof(Value)); 
	// Mengalokasikan memori untuk struktur Value baru
    newValue->value = value; 
	// Menetapkan nilai value simpul baru sesuai dengan nilai yang ditentukan
    newValue->right = newValue->left = NULL; 
	// Mengatur pointer right dan left menjadi NULL, menandakan simpul baru tidak memiliki anak
    newValue->height = 1; 
	// Mengatur ketinggian simpul baru menjadi 1, karena simpul ini adalah leaf node
	
    return newValue; 
	// Mengembalikan pointer ke simpul baru yang telah dibuat
	
}

int max(int getHeightLeft, int getHeightRight){ 
	// fungsi max menerima dua parameter bilangan yang akan dibandingkan
	
    if(getHeightLeft > getHeightRight){ 
	// memeriksa apakah nilai getHeightLeft lebih besar dari getHeightRight
	// jika iya, maka kembalikan nilai getHeightLeft sebagai nilai maximum
        return getHeightLeft; 
    }
    
    return getHeightRight; 
	// jika tidak, maka kembalikan nilai getHeightRight sebagai nilai maksimum
	
}

int getHeight(Value* current){ 
	// Menghitung tinggi simpul (node)
	
    if(current == NULL){
    	// Jika simpul saat ini adalah NULL, 
		// artinya tidak ada simpul, 
		// maka tinggi simpul tersebut adalah 0
        return 0; 
    }
    
    return current->height; 
	// Mengembalikan tinggi simpul saat ini
	
}

int setBalanceFactor(Value* current){ 
	// Mengatur faktor keseimbangan simpul
	
    if(current == NULL){
    	// Jika simpul saat ini adalah NULL, artinya tidak ada simpul, maka faktor keseimbangan adalah 0
        return 0; 
    }
    
    return getHeight(current->left) - getHeight(current->right);
    // Mengembalikan selisih tinggi antara anak kiri dan anak kanan simpul saat ini sebagai faktor keseimbangan
    
}

int setHeight(Value* current){ 
	// Mengatur tinggi simpul
	
    if(current == NULL){
    	// Jika simpul saat ini adalah NULL, artinya tidak ada simpul, maka tinggi simpul tersebut adalah 0
        return 0; 
    }
    
    return max(getHeight(current->left), getHeight(current->right)) + 1;
    // Mengembalikan tinggi maksimum antara anak kiri dan anak kanan simpul saat ini ditambah 1 sebagai tinggi simpul
    
}

Value* updateNode(Value* current){ 
	// Memperbarui simpul dengan tinggi dan faktor keseimbangan yang terkini
	
    if(current == NULL){
    	// Jika simpul saat ini adalah NULL, artinya tidak ada simpul, maka kembalikan simpul tersebut tanpa perubahan
        return current;  
    }
    
    current->height = setHeight(current); 
	// Mengatur tinggi simpul saat ini menggunakan fungsi setHeight
    current->balanceFactor = setBalanceFactor(current);
    // Mengatur faktor keseimbangan simpul saat ini menggunakan fungsi setBalanceFactor
    
    return current; 
	// Mengembalikan simpul yang diperbarui
	
}

Value* leftRotation(Value* current){
    // Melakukan rotasi ke kiri pada simpul saat ini
    
    Value *pivot = current->right;
    // Simpan simpul anak kanan sebagai pivot
    Value *childLeft = pivot->left;
    // Simpan simpul anak kiri dari pivot
    pivot->left = current;
    // Jadikan simpul saat ini menjadi anak kiri dari pivot
    current->right = childLeft;
    // Jadikan anak kiri pivot menjadi anak kanan simpul saat ini
    current = updateNode(current);
    // Perbarui simpul saat ini
    pivot = updateNode(pivot);
    // Perbarui pivot
    
    return pivot;
    // Kembalikan pivot sebagai simpul yang telah di-rotate
    
}

Value* rightRotation(Value* current){
    // Melakukan rotasi ke kanan pada simpul saat ini
    
    Value *pivot = current->left;
    // Simpan simpul anak kiri sebagai pivot
    Value *childRight = pivot->right;
    // Simpan simpul anak kanan dari pivot
    pivot->right = current;
    // Jadikan simpul saat ini menjadi anak kanan dari pivot
    current->left = childRight;
    // Jadikan anak kanan pivot menjadi anak kiri simpul saat ini
    current = updateNode(current);
    // Perbarui simpul saat ini
    pivot = updateNode(pivot);
    // Perbarui pivot
    
    return pivot;
    // Kembalikan pivot sebagai simpul yang telah di-rotate
    
}

Value* rotation(Value* current){
    // Fungsi untuk melakukan rotasi pada simpul saat ini berdasarkan faktor keseimbangan

    if(current == NULL){
    	// Jika simpul saat ini adalah NULL, artinya tidak ada simpul, maka kembalikan simpul tersebut tanpa perubahan
        return current;
    }

    // LL (Left-Left Case)
    if(current->balanceFactor > 1 && current->left->balanceFactor >= 0){
        // Jika faktor keseimbangan simpul saat ini lebih besar dari 1 (terlalu banyak simpul di anak kiri)
        // dan faktor keseimbangan anak kiri tidak negatif (simpul lebih banyak di anak kiri dari anak kanan atau seimbang)
        // maka lakukan rotasi ke kanan (rightRotation)
        return rightRotation(current);
    }

    // RR (Right-Right Case)
    else if(current->balanceFactor < -1 && current->right->balanceFactor <= 0){
        // Jika faktor keseimbangan simpul saat ini kurang dari -1 (terlalu banyak simpul di anak kanan)
        // dan faktor keseimbangan anak kanan tidak positif (simpul lebih banyak di anak kanan dari anak kiri atau seimbang)
        // maka lakukan rotasi ke kiri (leftRotation)
        return leftRotation(current);
    }

    // LR (Left-Right Case)
    else if(current->balanceFactor > 1 && current->left->balanceFactor < 0){
        // Jika faktor keseimbangan simpul saat ini lebih besar dari 1 (terlalu banyak simpul di anak kiri)
        // dan faktor keseimbangan anak kiri negatif (simpul lebih banyak di anak kanan dari anak kiri)
        // maka lakukan rotasi ke kiri (leftRotation) pada anak kiri dan kemudian rotasi ke kanan (rightRotation) pada simpul saat ini
        current->left = leftRotation(current->left);
        return rightRotation(current);
    }

    // RL (Right-Left Case)
    else if(current->balanceFactor < -1 && current->right->balanceFactor > 0){
        // Jika faktor keseimbangan simpul saat ini kurang dari -1 (terlalu banyak simpul di anak kanan)
        // dan faktor keseimbangan anak kanan positif (simpul lebih banyak di anak kiri dari anak kanan)
        // maka lakukan rotasi ke kanan (rightRotation) pada anak kanan dan kemudian rotasi ke kiri (leftRotation) pada simpul saat ini
        current->right = rightRotation(current->right);
        return leftRotation(current);
    }

    return current;
    // Jika tidak terjadi rotasi, kembalikan simpul saat ini tanpa perubahan
    
}

Value* insertValue(Value* root, int value){
    // Fungsi untuk menyisipkan nilai baru ke dalam pohon AVL

    if(root == NULL){
    	// Jika pohon masih kosong, buat simpul baru dengan nilai tersebut
        return createNode(value);
    }
	else if(value < root->value){
        // Jika nilai yang akan disisipkan lebih kecil dari nilai simpul saat ini,
        // sisipkan nilai ke anak kiri simpul saat ini secara rekursif
        root->left = insertValue(root->left, value);
    }
	else if(value > root->value){
        // Jika nilai yang akan disisipkan lebih besar dari nilai simpul saat ini,
        // sisipkan nilai ke anak kanan simpul saat ini secara rekursif
        root->right = insertValue(root->right, value);
    }
    
    return rotation(updateNode(root));
     // Lakukan rotasi dan update keseimbangan setelah sisip nilai
     
}

Value* searchValue(Value* root, int value) {
    // Fungsi untuk mencari nilai tertentu dalam pohon AVL

    if(root == NULL || root->value == value){
        // Jika pohon kosong atau nilai simpul saat ini sama dengan nilai yang dicari, kembalikan simpul saat ini
        return root;
    }
    else if(value < root->value){
        // Jika nilai yang dicari lebih kecil dari nilai simpul saat ini,
        // lanjutkan pencarian secara rekursif pada anak kiri simpul saat ini
        return searchValue(root->left, value);
    }
    else{
        // Jika nilai yang dicari lebih besar dari nilai simpul saat ini,
        // lanjutkan pencarian secara rekursif pada anak kanan simpul saat ini
        return searchValue(root->right, value);
    }
}

Value* deleteValue(Value* root, int deletedValue) {
    // Fungsi untuk menghapus simpul dengan nilai tertentu dari pohon AVL

    if(root == NULL){
        // Jika pohon kosong, kembalikan simpul saat ini
        return root;
    }
    else if(deletedValue < root->value){
        // Jika nilai yang akan dihapus lebih kecil dari nilai simpul saat ini,
        // lanjutkan pencarian secara rekursif pada anak kiri simpul saat ini
        root->left = deleteValue(root->left, deletedValue);
    }
    else if(deletedValue > root->value){
        // Jika nilai yang akan dihapus lebih besar dari nilai simpul saat ini,
        // lanjutkan pencarian secara rekursif pada anak kanan simpul saat ini
        root->right = deleteValue(root->right, deletedValue);
    }
    else if(deletedValue == root->value) {
        // Jika nilai yang akan dihapus sama dengan nilai simpul saat ini

        if(root->left == NULL && root->right == NULL){
            // Node to delete has no children
            // Hapus simpul saat ini dari memori dan atur pointer root menjadi NULL
            free(root);
            root = NULL;
        }
        else if(root->left != NULL && root->right == NULL){
            // Node to delete has only left child
            // Simpan pointer ke anak kiri simpul saat ini
            // Hapus simpul saat ini dari memori dan atur pointer root menjadi anak kiri
            Value *temp = root->left;
            free(root);
            root = temp;
        }
        else if(root->left == NULL && root->right != NULL){
            // Node to delete has only right child
            // Simpan pointer ke anak kanan simpul saat ini
            // Hapus simpul saat ini dari memori dan atur pointer root menjadi anak kanan
            Value *temp = root->right;
            free(root);
            root = temp;
        }
        else if(root->left != NULL && root->right != NULL){
            // Node to delete has both left and right children
            // Cari nilai terbesar di anak kiri simpul saat ini sebagai pengganti simpul saat ini
            // Ganti nilai simpul saat ini dengan nilai terbesar tersebut
            // Hapus nilai terbesar tersebut dari anak kiri simpul saat ini
            Value *temp = root->left;
            while (temp->right) {
                temp = temp->right;
            }
            root->value = temp->value;
            root->left = deleteValue(root->left, temp->value);
        }
    }
    
    return rotation(updateNode(root));
    // Lakukan rotasi dan pembaruan setelah operasi penghapusan
}

void preOrder(Value* root){
    // Traversal PreOrder: mengunjungi simpul saat ini terlebih dahulu, kemudian anak kiri, dan anak kanan

    if(root){
        // Jika simpul saat ini tidak kosong
        printf("%d ", root->value);  
		// Cetak nilai simpul saat ini
        preOrder(root->left);  
		// Lakukan rekursi pada anak kiri
        preOrder(root->right); 
		// Lakukan rekursi pada anak kanan
    }
    
}

void inOrder(Value* root){
    // Traversal InOrder: mengunjungi anak kiri terlebih dahulu, kemudian simpul saat ini, dan anak kanan

    if(root){
        // Jika simpul saat ini tidak kosong
        inOrder(root->left);  
		// Lakukan rekursi pada anak kiri
        printf("%d ", root->value);  
		// Cetak nilai simpul saat ini
        inOrder(root->right);  
		// Lakukan rekursi pada anak kanan
    }
    
}

void postOrder(Value* root){
    // Traversal PostOrder: mengunjungi anak kiri terlebih dahulu, kemudian anak kanan, dan simpul saat ini terakhir

    if(root){
        // Jika simpul saat ini tidak kosong
        postOrder(root->left);  
		// Lakukan rekursi pada anak kiri
        postOrder(root->right);  
		// Lakukan rekursi pada anak kanan
        printf("%d ", root->value);  
		// Cetak nilai simpul saat ini
    }
    
}

void printTraversal(Value* root){
	
	printf("Preorder: ");
    preOrder(root);  
	// Menampilkan hasil penelusuran Preorder
    puts("");
    printf("Inorder: ");
    inOrder(root);  
	// Menampilkan hasil penelusuran Inorder
    puts("");
    printf("Postorder: ");
    postOrder(root);  
	// Menampilkan hasil penelusuran Postorder
    puts("");
    
}

void exitScreen(){
	
    system("cls");  
	// Membersihkan layar konsol (tergantung pada sistem operasi)
    puts("Thank You");  
	// Menampilkan teks "Thank You" di layar konsol
    printf("Press Enter to exit");  
	// Menampilkan teks "Press Enter to exit" di layar konsol
    getchar();  
	// Menunggu pengguna menekan tombol Enter
    exit(0);  
	// Keluar dari program dengan status 0 (menandakan keluar dengan sukses)
	
}

void menuList(){
	
    int inputNumber;
    Value *root = NULL; // deklrasi dan insialisasikan bahwa root awalnya adalah NULL
    
    do{
    	system("cls");
        puts("1. Insertion");  
		// Menampilkan pilihan untuk melakukan penambahan data
        puts("2. Deletion");  
		// Menampilkan pilihan untuk melakukan penghapusan data
        puts("3. Traversal");  
		// Menampilkan pilihan untuk melakukan menampilkan hasil traversal data
        puts("4. Exit");  
		// Menampilkan pilihan untuk keluar dari program
        printf("Choose: ");  
		// Menampilkan pesan untuk memilih opsi

        scanf("%d", &inputNumber); 
		// Membaca input dari pengguna untuk memilih opsi
        getchar();  
		// Menggunakan getchar() untuk membersihkan karakter newline (\n) dari input

        int valueToInput;
        int valueToDelete;

        switch(inputNumber){
            case 1:
                printf("Insert: "); 
				 // Meminta pengguna memasukkan nilai yang akan ditambahkan
                scanf("%d", &valueToInput);  
				// Membaca nilai yang akan ditambahkan
                getchar();  
				// Menggunakan getchar() untuk membersihkan karakter newline (\n) dari input
                root = insertValue(root, valueToInput);  
				// Menambahkan nilai ke dalam pohon
				printf("Value %d was inserted\n", valueToInput);
                break;
            case 2:
                printf("Delete: "); 
				// Meminta pengguna memasukkan nilai yang akan dihapus
                scanf("%d", &valueToDelete);  
				// Membaca nilai yang akan dihapus
                getchar();  
				// Menggunakan getchar() untuk membersihkan karakter newline (\n) dari input
				
                if(searchValue(root, valueToDelete) != NULL){
                    root = deleteValue(root, valueToDelete);  
					// Menghapus nilai dari pohon
                    puts("Data Found");
                    printf("Value %d was deleted\n", valueToDelete);
                } 
                else if(searchValue(root, valueToDelete) == NULL){
                    puts("Data not found");  
					// Menampilkan pesan bahwa nilai tidak ditemukan
                }
                root = deleteValue(root, valueToDelete);  
                
                break;
            case 3:
        		printTraversal(root);
                break;
            case 4:
                exitScreen();  
				// Keluar dari program
                break;
        }
        puts("Press enter to continue...");
        getchar();
    }while(inputNumber >= 1 && inputNumber <= 4); 
	 // Melakukan pengulangan selama inputNumber berada dalam rentang 1-4
	 
}

int main(){
	
    menuList(); 
	// memanggil fungsi untuk menampilkan list menu
    return 0;
    
}
