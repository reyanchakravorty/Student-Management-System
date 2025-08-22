#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Student structure
struct Student {
    int rollNo;
    string name;
    float marks;
};

// Add a student
void addStudent() {
    Student s;
    cout << "Enter Roll No: ";
    cin >> s.rollNo;
    cin.ignore(); // clear newline
    cout << "Enter Name: ";
    getline(cin, s.name);
    cout << "Enter Marks: ";
    cin >> s.marks;

    ofstream outFile("students.txt", ios::app);
    outFile << s.rollNo << " " << s.name << " " << s.marks << endl;
    outFile.close();
    cout << "Student added successfully!\n";
}

// Display all students
void displayStudents() {
    ifstream inFile("students.txt");
    if (!inFile) {
        cout << "No records found.\n";
        return;
    }

    Student s;
    cout << "\n--- Student Records ---\n";
    while (inFile >> s.rollNo) {
        inFile.ignore();
        getline(inFile, s.name);
        inFile >> s.marks;
        inFile.ignore();
        cout << "Roll No: " << s.rollNo << "\nName: " << s.name << "\nMarks: " << s.marks << "\n\n";
    }
    inFile.close();
}

// Update a student
void updateStudent() {
    ifstream inFile("students.txt");
    if (!inFile) { cout << "No records found.\n"; return; }

    Student s;
    bool found = false;
    ofstream tempFile("temp.txt");

    int rollToUpdate;
    cout << "Enter Roll No to update: ";
    cin >> rollToUpdate;
    cin.ignore();

    while (inFile >> s.rollNo) {
        inFile.ignore();
        getline(inFile, s.name);
        inFile >> s.marks;
        inFile.ignore();

        if (s.rollNo == rollToUpdate) {
            cout << "Enter new Name: ";
            getline(cin, s.name);
            cout << "Enter new Marks: ";
            cin >> s.marks;
            cin.ignore();
            found = true;
        }

        tempFile << s.rollNo << " " << s.name << " " << s.marks << endl;
    }

    inFile.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) cout << "Student record updated successfully!\n";
    else cout << "Student not found.\n";
}

// Delete a student
void deleteStudent() {
    ifstream inFile("students.txt");
    if (!inFile) { cout << "No records found.\n"; return; }

    Student s;
    bool found = false;
    ofstream tempFile("temp.txt");

    int rollToDelete;
    cout << "Enter Roll No to delete: ";
    cin >> rollToDelete;
    cin.ignore();

    while (inFile >> s.rollNo) {
        inFile.ignore();
        getline(inFile, s.name);
        inFile >> s.marks;
        inFile.ignore();

        if (s.rollNo == rollToDelete) {
            found = true;
            continue; // skip writing this record
        }
        tempFile << s.rollNo << " " << s.name << " " << s.marks << endl;
    }

    inFile.close();
    tempFile.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) cout << "Student record deleted successfully!\n";
    else cout << "Student not found.\n";
}

// Main menu
int main() {
    int choice;
    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n2. Display Students\n3. Update Student\n4. Delete Student\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

