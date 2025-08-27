#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

struct Task {
    int ID = 0;
    char topic[30];
    char description[200];
    char dueDate[10];
    bool completed = true;
};

//Forward declarations 
void displayMenu();
void addTask();
void displayAllTasks();
void searchTask();
void updateTask();
void taskCompleted();
void isValid();
void printDescriptionWithLineLimit();

int main() {
    int choice = 0;

    // Main loop.
    do {
        displayMenu();
        cout << "Enter your choice: " << endl;
        cin >> choice;
        isValid();  //Error handling in case of non numeric input 
        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                displayAllTasks();
                break;
            case 3:
                searchTask();
                break;
            case 4:
                updateTask();
                break;
            case 5:
                taskCompleted();
                break;
            case 6:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
        cout << endl;
    }while(choice != 6);
    return 0;
}

void isValid() {
    if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
}

void displayMenu() { // Main menu options.
    cout << "--- To-Do List Menu ---" << endl;
    cout << "1. Add Task" << endl;
    cout << "2. Display All Tasks" << endl;
    cout << "3. Search for a Task" << endl;
    cout << "4. Update a Task" << endl;
    cout << "5. Mark a Task Completed" << endl;
    cout << "6. Exit" << endl;
    cout << "-----------------------" << endl;
}

void addTask() { // Adds a new task todo.
    Task task;
    cout << "Enter Task ID: ";
    cin >> task.ID;
    isValid(); // non numeric input for ID
    
    cout << "Enter task heading: ";
    cin.ignore();
    cin.getline(task.topic, 30);

    cout << "Enter task Description: ";
    cin.ignore();
    cin.getline(task.description, 200);

    cout << "Enter Due Date: DD-MM-YYYY: ";
    cin.ignore();
    cin.getline(task.dueDate, 10);

    ofstream outFile("task.dat", ios::binary | ios::app);

    if(!outFile) {
        cerr << "Error: Could not open file for writing. " << endl;
        return;
    }
    task.completed = false;
    outFile.write(reinterpret_cast<const char*>(&task), sizeof(Task));
    outFile.close();

    cout << "Task record added successfully." << endl;
}

void printDescriptionWithLineLimit(const string& des, int line_limit) {
    if (des.empty()) return;

    size_t start_pos = 0;
    while (start_pos < des.length()) {
        size_t length = min(static_cast<size_t>(line_limit), des.length() - start_pos);
        cout << des.substr(start_pos, length) << endl;
        start_pos += length;
    }
}

void displayAllTasks() {

    ifstream inFile("task.dat", ios::binary);
    if(!inFile) {
        cerr << "Error: Could not open file for reading. " << endl;
        return;
    }
    int option = 0;
    cout << "Do yo wish to see active tasks or completed? " << endl
         << "1. Active Tasks" << endl
         << "2. Completed"    << endl
         << "3. All"          << endl;
    cin >> option;
    isValid();

    switch (option) {
        case 1: {
            Task task;

            while (inFile.read(reinterpret_cast<char*>(&task), sizeof(Task))) {
                if (!task.completed) {
                    const int max_length = 40;
                    cout << "Topic: " << task.topic << endl;
                    cout << "DueDate: " << task.dueDate << " ID: " << task.ID << endl;
                    printDescriptionWithLineLimit(task.description, max_length);
                    cout << endl;
                }
            }
            break;
        }
        case 2: {
            Task task;
            while (inFile.read(reinterpret_cast<char*>(&task), sizeof(Task))) {
                if (task.completed) {
                    const int max_length = 40;
                    cout << "Topic: " << task.topic << endl;
                    cout << "DueDate: " << task.dueDate << " ID: " << task.ID << endl;
                    printDescriptionWithLineLimit(task.description, max_length);
                    cout << endl;
                }
            }
            break;
        }
        case 3: {
            Task task;
            while (inFile.read(reinterpret_cast<char*>(&task), sizeof(Task))) {
                const int max_length = 40;
                cout << "Topic: " << task.topic << endl;
                cout << "DueDate: " << task.dueDate << " ID: " << task.ID << endl;
                printDescriptionWithLineLimit(task.description, max_length);
                cout << endl;
            }
            break;
        }
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
    }
    inFile.close();
}

void searchTask() {
    Task task;
    int searchId = 0;
    bool found = false;

    cout << "Enter task ID: ";
    cin >> searchId;
    isValid();

    ifstream inFile("task.dat", ios::binary);
    if (!inFile) {
        cerr << "Error: Could not open file for reading. " << endl;
        return;
    }

    // Read through the file to find a matching ID
    while (inFile.read(reinterpret_cast<char*>(&task), sizeof(Task))) {
        if ( task.ID == searchId ) {
            found = true;
            cout << "Task ID: " << task.ID << endl;
            cout << "DueDate: " << task.dueDate << " ID: " << task.ID << endl;
            const int max_length = 40;
            printDescriptionWithLineLimit(task.description, max_length);
            break;
        }
    }
    inFile.close();

    if (!found) {
        cout << "No task found with ID:" << searchId << endl;
    }
}

void updateTask() {
    Task task;
    int searchId = 0;
    cout << "Enter task ID: ";
    cin >> searchId;
    isValid();
    bool found = false;

    fstream file("task.dat", ios::in | ios::out |ios::binary);
    if (!file) {
        cerr << "Error: Could not open file for reading. " << endl;
        return;
    }
    while (file.read(reinterpret_cast<char*>(&task), sizeof(Task))) {
        if ( task.ID == searchId ) {
            cout << "Task ID: " << task.ID << endl;

            cout << "Enter new ID " << endl;
            cin >> task.ID;
            isValid();
            cout << "Current Due Date: " << task.dueDate << endl;
            cout  << "Enter new Due Date: " << endl;
            cin.ignore();
            cin.getline(task.dueDate, 10);

            cout << "Current Topic: " << task.topic << endl;
            cout << "Enter new Topic " << endl;
            cin.ignore();
            cin.getline(task.topic, 30);

            cout << "Current Description: "  <<endl;
            const int max_length = 40;
            printDescriptionWithLineLimit(task.description, max_length);
            cout << "Enter new Description " << endl;
            cin.ignore();
            cin.getline(task.description, 200);

            long pos = -1 * static_cast<long>(sizeof(Task));
            file.seekp(pos, ios::cur);

            file.write(reinterpret_cast<char*>(&task), sizeof(Task));

            found = true;
            cout << "Task updated." << endl;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "No task found with ID:" << searchId << endl;
    }
}

void taskCompleted() {
    Task task;
    int searchId = 0;
    cout << "Enter task ID: ";
    cin >> searchId;
    isValid();
    bool found = false;

    fstream file("task.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cerr << "Error: Could not open file for reading. " << endl;
        return;
    }
    while (file.read(reinterpret_cast<char*>(&task), sizeof(Task))) {
        if ( task.ID == searchId ) {
            cout << "Task found." << endl;
            task.completed = true;

            long pos = -1 * static_cast<long>(sizeof(Task));
            file.seekp(pos, ios::cur);

            file.write(reinterpret_cast<char*>(&task), sizeof(Task));
            found = true;
            cout << "Task updated." << endl;
            break;
        }
    }
    file.close();
    if (!found) {
        cout << "No task found with ID:" << searchId << endl;
    }
}



