#include <iostream>
#include <string>
using namespace std;

#define SIZE 100

struct Course {
    string name;
    Course *next;
};

struct Student {
    int roll;
    string name;
    string dept;
    Course *courses;
    Student *next;
};

struct Hash {
    int roll;
    Student *s;
    Hash *next;
};

Student *head = NULL;
Hash *h[SIZE] = {NULL};

int hashFunction(int roll) {
    return roll % SIZE;
}

Student* searchStudent(int roll) {
    int index = hashFunction(roll);
    Hash *t = h[index];

    while (t != NULL) {
        if (t->roll == roll)
            return t->s;
        t = t->next;
    }

    return NULL;
}

void insertHash(Student *s) {
    int index = hashFunction(s->roll);

    Hash *n = new Hash;
    n->roll = s->roll;
    n->s = s;
    n->next = h[index];
    h[index] = n;
}

void deleteHash(int roll) {
    int index = hashFunction(roll);
    Hash *t = h[index], *prev = NULL;

    while (t != NULL) {
        if (t->roll == roll) {
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

void registerStudent() {
    Student *n = new Student;

    cout << "Enter Roll Number: ";
    cin >> n->roll;

    if (searchStudent(n->roll) != NULL) {
        cout << "Roll Number already exists!\n";
        delete n;
        return;
    }

    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, n->name);

    cout << "Enter Department: ";
    getline(cin, n->dept);

    n->courses = NULL;
    n->next = head;
    head = n;

    insertHash(n);

    cout << "Student registered successfully!\n";
}

void updateStudent() {
    int roll;

    cout << "Enter Roll Number: ";
    cin >> roll;

    Student *s = searchStudent(roll);

    if (s == NULL) {
        cout << "Student not found!\n";
        return;
    }

    cout << "Enter New Name: ";
    cin.ignore();
    getline(cin, s->name);

    cout << "Enter New Department: ";
    getline(cin, s->dept);

    cout << "Student updated successfully!\n";
}

void enrollStudent() {
    int roll;
    string name;

    cout << "Enter Roll Number: ";
    cin >> roll;

    Student *s = searchStudent(roll);

    if (s == NULL) {
        cout << "Student not found!\n";
        return;
    }

    cout << "Enter Course Name: ";
    cin.ignore();
    getline(cin, name);

    Course *t = s->courses;

    while (t != NULL) {
        if (t->name == name) {
            cout << "Already enrolled in this course!\n";
            return;
        }
        t = t->next;
    }

    Course *n = new Course;
    n->name = name;
    n->next = s->courses;
    s->courses = n;

    cout << "Course enrolled successfully!\n";
}

void withdrawStudent() {
    int roll;
    string name;

    cout << "Enter Roll Number: ";
    cin >> roll;

    Student *s = searchStudent(roll);

    if (s == NULL) {
        cout << "Student not found!\n";
        return;
    }

    cout << "Enter Course Name: ";
    cin.ignore();
    getline(cin, name);

    Course *t = s->courses;
    Course *prev = NULL;

    while (t != NULL) {
        if (t->name == name) {
            if (prev == NULL)
                s->courses = t->next;
            else
                prev->next = t->next;

            delete t;

            cout << "Course withdrawn successfully!\n";
            return;
        }

        prev = t;
        t = t->next;
    }

    cout << "Course not found!\n";
}

void removeStudent() {
    int roll;

    cout << "Enter Roll Number: ";
    cin >> roll;

    Student *t = head, *prev = NULL;

    while (t != NULL) {
        if (t->roll == roll) {
            if (prev == NULL)
                head = t->next;
            else
                prev->next = t->next;

            deleteHash(roll);

            Course *c = t->courses;

            while (c != NULL) {
                Course *temp = c;
                c = c->next;
                delete temp;
            }

            delete t;

            cout << "Student removed successfully!\n";
            return;
        }

        prev = t;
        t = t->next;
    }

    cout << "Student not found!\n";
}

void displayStudents() {
    Student *t = head;

    if (t == NULL) {
        cout << "No student records available!\n";
        return;
    }

    while (t != NULL) {
        cout << "\nRoll Number: " << t->roll;
        cout << "\nStudent Name: " << t->name;
        cout << "\nDepartment: " << t->dept;
        cout << "\nCourses: ";

        Course *c = t->courses;

        if (c == NULL)
            cout << "None";

        while (c != NULL) {
            cout << c->name << " ";
            c = c->next;
        }

        cout << endl;
        t = t->next;
    }
}

void searchByRollNo() {
    int roll;

    cout << "Enter Roll Number: ";
    cin >> roll;

    Student *s = searchStudent(roll);

    if (s == NULL) {
        cout << "Student not found!\n";
    } else {
        cout << "\nStudent Found!\n";
        cout << "Roll Number: " << s->roll << endl;
        cout << "Student Name: " << s->name << endl;
        cout << "Department: " << s->dept << endl;
        cout << "Courses: ";

        Course *c = s->courses;

        if (c == NULL)
            cout << "None";

        while (c != NULL) {
            cout << c->name << " ";
            c = c->next;
        }

        cout << endl;
    }
}

int main() {
    int choice;

    do {
        cout << "\n===== UNIVERSITY REGISTRATION SYSTEM =====\n";
        cout << "1. Register Student\n";
        cout << "2. Update Student\n";
        cout << "3. Enroll in Course\n";
        cout << "4. Withdraw from Course\n";
        cout << "5. Remove Student\n";
        cout << "6. Display Students\n";
        cout << "7. Search Student\n";
        cout << "8. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerStudent();
                break;

            case 2:
                updateStudent();
                break;

            case 3:
                enrollStudent();
                break;

            case 4:
                withdrawStudent();
                break;

            case 5:
                removeStudent();
                break;

            case 6:
                displayStudents();
                break;

            case 7:
                searchByRollNo();
                break;

            case 8:
                cout << "Program ended!\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 8);

    return 0;
}
