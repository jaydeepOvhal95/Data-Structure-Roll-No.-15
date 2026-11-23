#include <iostream>
#include <string>
using namespace std;

#define SIZE 100

struct Product {
    int id;
    string name;
    float price;
    int quantity;
    Product *next;
};

struct Hash {
    int id;
    Product *p;
    Hash *next;
};

Product *head = NULL;
Hash *h[SIZE] = {NULL};

int hashFunction(int id) {
    return id % SIZE;
}

Product* searchProduct(int id) {
    int index = hashFunction(id);
    Hash *t = h[index];

    while (t != NULL) {
        if (t->id == id)
            return t->p;
        t = t->next;
    }
    return NULL;
}

void insertHash(Product *p) {
    int index = hashFunction(p->id);

    Hash *n = new Hash;
    n->id = p->id;
    n->p = p;
    n->next = h[index];
    h[index] = n;
}

void deleteHash(int id) {
    int index = hashFunction(id);
    Hash *t = h[index], *prev = NULL;

    while (t != NULL) {
        if (t->id == id) {
            if (prev == NULL)
                h[index] = t->next;
            else
                prev->next = t->next;

            delete t;
            return;
        }
        prev = t;
        t = t->next;
    }
}

void addProduct() {
    Product *n = new Product;

    cout << "Enter Product ID: ";
    cin >> n->id;

    if (searchProduct(n->id) != NULL) {
        cout << "Product ID already exists!\n";
        delete n;
        return;
    }

    cout << "Enter Product Name: ";
    cin.ignore();
    getline(cin, n->name);

    cout << "Enter Price: ";
    cin >> n->price;

    cout << "Enter Quantity: ";
    cin >> n->quantity;

    n->next = head;
    head = n;

    insertHash(n);

    cout << "Product added successfully!\n";
}

void updateProduct() {
    int id;

    cout << "Enter Product ID: ";
    cin >> id;

    Product *p = searchProduct(id);

    if (p == NULL) {
        cout << "Product not found!\n";
        return;
    }

    cout << "Enter New Name: ";
    cin.ignore();
    getline(cin, p->name);

    cout << "Enter New Price: ";
    cin >> p->price;

    cout << "Enter New Quantity: ";
    cin >> p->quantity;

    cout << "Product updated successfully!\n";
}

void removeProduct() {
    int id;

    cout << "Enter Product ID: ";
    cin >> id;

    Product *t = head, *prev = NULL;

    while (t != NULL) {
        if (t->id == id) {
            if (prev == NULL)
                head = t->next;
            else
                prev->next = t->next;

            deleteHash(id);
            delete t;

            cout << "Product removed successfully!\n";
            return;
        }

        prev = t;
        t = t->next;
    }

    cout << "Product not found!\n";
}

void displayProducts() {
    Product *t = head;

    if (t == NULL) {
        cout << "No products available!\n";
        return;
    }

    while (t != NULL) {
        cout << "\nProduct ID: " << t->id;
        cout << "\nProduct Name: " << t->name;
        cout << "\nPrice: " << t->price;
        cout << "\nQuantity: " << t->quantity << "\n";

        t = t->next;
    }
}

void searchByID() {
    int id;

    cout << "Enter Product ID: ";
    cin >> id;

    Product *p = searchProduct(id);

    if (p == NULL) {
        cout << "Product not found!\n";
    } else {
        cout << "\nProduct Found!\n";
        cout << "Product ID: " << p->id << endl;
        cout << "Product Name: " << p->name << endl;
        cout << "Price: " << p->price << endl;
        cout << "Quantity: " << p->quantity << endl;
    }
}

int main() {
    int choice;

    do {
        cout << "\n===== E-COMMERCE INVENTORY SYSTEM =====\n";
        cout << "1. Add Product\n";
        cout << "2. Update Product\n";
        cout << "3. Remove Product\n";
        cout << "4. Display Products\n";
        cout << "5. Search Product\n";
        cout << "6. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addProduct();
                break;

            case 2:
                updateProduct();
                break;

            case 3:
                removeProduct();
                break;

            case 4:
                displayProducts();
                break;

            case 5:
                searchByID();
                break;

            case 6:
                cout << "Program ended!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
