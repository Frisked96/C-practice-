#include <iostream>
#include <fstream>
#include <string>
#include <limits> // Required for numeric_limits

// Using the standard namespace to avoid prefixing (e.g., std::cout)
using namespace std;

// Define a structure to hold the data for a single student.
// Using a struct is a good way to group related data together.
struct Student {
    int id;
    char name[50]; // Using a char array for simplicity in binary file I/O
    double grade;
};

// --- Function Prototypes ---
// Declaring functions before they are used helps organize the code and is required by the compiler.
void addStudentRecord();
void displayAllRecords();
void searchStudentRecord();
void updateStudentRecord();
void displayMenu();

int main() {
    int choice;

    // Main program loop. It will continue to show the menu until the user chooses to exit.
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        // This block handles cases where the user enters non-numeric input.
        if (cin.fail()) {
            cin.clear(); // Clear the error flag on cin
            // Ignore the rest of the line to prevent an infinite loop
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0; // Set choice to an invalid value to trigger the default case
        }
        
        // Clears the input buffer after reading the choice, which is important before reading string data.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');


        switch (choice) {
            case 1:
                addStudentRecord();
                break;
            case 2:
                displayAllRecords();
                break;
            case 3:
                searchStudentRecord();
                break;
            case 4:
                updateStudentRecord();
                break;
            case 5:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
        cout << endl;

    } while (choice != 5);

    return 0;
}

/**
 * @brief Displays the main menu options to the user.
 */
void displayMenu() {
    cout << "--- Student Record System ---" << endl;
    cout << "1. Add Student Record" << endl;
    cout << "2. Display All Records" << endl;
    cout << "3. Search for a Student" << endl;
    cout << "4. Update a Student Record" << endl;
    cout << "5. Exit" << endl;
    cout << "---------------------------" << endl;
}

/**
 * @brief Adds a new student record to the binary file.
 */
void addStudentRecord() {
    Student student;

    cout << "Enter Student ID: ";
    cin >> student.id;
    // Handle non-numeric input for ID
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID. Please enter a number." << endl;
        return;
    }

    cout << "Enter Student Name: ";
    cin.ignore(); // Clears the newline character left by `cin >> student.id`
    cin.getline(student.name, 50);

    cout << "Enter Student Grade: ";
    cin >> student.grade;
    // Handle non-numeric input for grade
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid grade. Please enter a number." << endl;
        return;
    }

    // Open the file in binary append mode. 'app' means append, 'binary' is for non-text data.
    // 'ios::out' is implied with 'app'.
    ofstream outFile("students.dat", ios::binary | ios::app);

    if (!outFile) {
        cerr << "Error: Could not open file for writing." << endl;
        return;
    }

    // Write the student object to the file.
    // We cast the address of the student object to a char pointer.
    outFile.write(reinterpret_cast<const char*>(&student), sizeof(Student));
    outFile.close();

    cout << "Student record added successfully." << endl;
}

/**
 * @brief Reads and displays all student records from the file.
 */
void displayAllRecords() {
    Student student;

    // Open the file for reading in binary mode.
    ifstream inFile("students.dat", ios::binary);

    if (!inFile) {
        cerr << "Error: Could not open file for reading, or no records exist yet." << endl;
        return;
    }

    cout << "\n--- All Student Records ---" << endl;
    cout << "ID\tName\t\tGrade" << endl;
    cout << "---------------------------" << endl;

    // Read records one by one until the end of the file is reached.
    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        cout << student.id << "\t" << student.name << "\t\t" << student.grade << endl;
    }

    inFile.close();
}

/**
 * @brief Searches for a specific student record by ID and displays it.
 */
void searchStudentRecord() {
    int searchId;
    Student student;
    bool found = false;

    cout << "Enter Student ID to search for: ";
    cin >> searchId;

    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        cerr << "Error: Could not open file for reading." << endl;
        return;
    }

    // Read through the file to find a matching ID.
    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.id == searchId) {
            cout << "\n--- Record Found ---" << endl;
            cout << "ID: " << student.id << endl;
            cout << "Name: " << student.name << endl;
            cout << "Grade: " << student.grade << endl;
            found = true;
            break; // Exit the loop once the record is found
        }
    }

    inFile.close();

    if (!found) {
        cout << "No student found with ID: " << searchId << endl;
    }
}

/**
 * @brief Finds a student record by ID and allows the user to update it.
 */
void updateStudentRecord() {
    int updateId;
    Student student;
    bool found = false;

    cout << "Enter Student ID to update: ";
    cin >> updateId;

    // Open the file for both reading and writing in binary mode.
    fstream file("students.dat", ios::in | ios::out | ios::binary);

    if (!file) {
        cerr << "Error: Could not open file." << endl;
        return;
    }

    // Read through the file to find the matching record.
    while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.id == updateId) {
            cout << "--- Record Found ---" << endl;
            cout << "Current Name: " << student.name << endl;
            cout << "Current Grade: " << student.grade << endl;

            // Get new data from the user
            cout << "\nEnter new name: ";
            cin.ignore();
            cin.getline(student.name, 50);

            cout << "Enter new grade: ";
            cin >> student.grade;

            // Move the file pointer back to the beginning of the record we just read.
            long pos = -1 * static_cast<long>(sizeof(Student));
            file.seekp(pos, ios::cur);

            // Write the updated record over the old one.
            file.write(reinterpret_cast<const char*>(&student), sizeof(Student));

            found = true;
            cout << "Record updated successfully." << endl;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "No student found with ID: " << updateId << endl;
    }
}