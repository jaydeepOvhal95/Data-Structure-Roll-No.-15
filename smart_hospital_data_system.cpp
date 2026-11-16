#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Patient
{
    int id;
    string name;
    int age;
    string disease;

    Patient* next;      // Linked List pointer
    Patient* hashNext;  // Hash Table pointer
};

Patient* head = NULL;

const int SIZE = 10;
Patient* hashTable[SIZE] = {NULL};

// Hash Function
int hashFunction(int id)
{
    return id % SIZE;
}

// Register Patient
void registerPatient()
{
    Patient* p = new Patient;

    cout << "Enter Patient ID: ";
    cin >> p->id;

    // Check for duplicate ID
    int index = hashFunction(p->id);
    Patient* temp = hashTable[index];

    while (temp != NULL)
    {
        if (temp->id == p->id)
        {
            cout << "Patient ID already exists!\n";
            delete p;
            return;
        }

        temp = temp->hashNext;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Patient Name: ";
    getline(cin, p->name);

    cout << "Enter Age: ";
    cin >> p->age;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Disease: ";
    getline(cin, p->disease);

    // Insert into Linked List
    p->next = head;
    head = p;

    // Insert into Hash Table using Chaining
    p->hashNext = hashTable[index];
    hashTable[index] = p;

    cout << "Patient registered successfully!\n";
}

// Search Patient
void searchPatient()
{
    int id;

    cout << "Enter Patient ID to search: ";
    cin >> id;

    int index = hashFunction(id);

    Patient* temp = hashTable[index];

    while (temp != NULL)
    {
        if (temp->id == id)
        {
            cout << "\nPatient Found!\n";
            cout << "ID: " << temp->id << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Age: " << temp->age << endl;
            cout << "Disease: " << temp->disease << endl;

            return;
        }

        temp = temp->hashNext;
    }

    cout << "Patient not found!\n";
}

// Display All Patients
void displayPatients()
{
    Patient* temp = head;

    if (temp == NULL)
    {
        cout << "No patient records available.\n";
        return;
    }

    cout << "\n--- All Patient Records ---\n";

    while (temp != NULL)
    {
        cout << "\nPatient ID: " << temp->id << endl;
        cout << "Name: " << temp->name << endl;
        cout << "Age: " << temp->age << endl;
        cout << "Disease: " << temp->disease << endl;

        temp = temp->next;
    }
}

// Delete Patient
void deletePatient()
{
    int id;

    cout << "Enter Patient ID to delete: ";
    cin >> id;

    int index = hashFunction(id);

    // Remove from Hash Table
    Patient* temp = hashTable[index];
    Patient* prevHash = NULL;

    while (temp != NULL && temp->id != id)
    {
        prevHash = temp;
        temp = temp->hashNext;
    }

    if (temp == NULL)
    {
        cout << "Patient not found!\n";
        return;
    }

    if (prevHash == NULL)
        hashTable[index] = temp->hashNext;
    else
        prevHash->hashNext = temp->hashNext;

    // Remove from Linked List
    Patient* current = head;
    Patient* prev = NULL;

    while (current != NULL && current->id != id)
    {
        prev = current;
        current = current->next;
    }

    if (prev == NULL)
        head = current->next;
    else
        prev->next = current->next;

    delete current;

    cout << "Patient deleted successfully!\n";
}

// Main Function
int main()
{
    int choice;

    do
    {
        cout << "\n--- Hospital Management System ---\n";

        cout << "1. Register Patient\n";
        cout << "2. Search Patient\n";
        cout << "3. Display All Patients\n";
        cout << "4. Delete Patient\n";
        cout << "5. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                registerPatient();
                break;

            case 2:
                searchPatient();
                break;

            case 3:
                displayPatients();
                break;

            case 4:
                deletePatient();
                break;

            case 5:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
