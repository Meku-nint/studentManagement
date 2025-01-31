#include"header.h"
class Admin {
private:
    string name;
    Admin* next;
    Admin* prev;
    string user_name;
    string password;

public:
    static Admin* head;
    static Admin* tail; 
    Admin() : next(nullptr), prev(nullptr) {}         
    // Prompts the user to enter the admin username and password, allowing up to three attempts before exiting if incorrect. 
    void loginAsAdmin() {
        system("cls");
        cout<<"\n\nEnter user name and password to login as admin"<<endl;
        for(int i=3;i>0;i--) {
        cout << "\n\t\tEnter user name: ";
        getline(cin,user_name);
        cout << "\t\tEnter password: ";
        getline(cin,password);
        if(user_name != "admin" ||password != "admin") {
            system("cls");
            cout<<"you have left "<<i-1<<"  attempt"<<endl;
            if(i==1) {
                exit(0);
            }
        }
        else{
            break;
        }
       
        }   
    }
// This function displays the Admin Panel menu with options to add students, departments, courses, edit student info, view student lists, and add lecturers.
// It takes user input to perform the corresponding action, looping until a valid option (1-7) is selected. If an invalid choice is made, an error message is displayed.
    void adminMenu() {

        while (true) {
            system("cls");
            cout << "\n\n\t\t\t\tWelcome to Admin Panel" << endl << endl;
            cout << "\t\t\t\t\t1. Add Student" << endl;
            cout<<  "\t\t\t\t\t2. Add Lecturer" << endl<<endl;
            cout << "\t\t\t\t\t3. Add Department" << endl;
            cout << "\t\t\t\t\t4. Add Course" << endl;
            cout << "\t\t\t\t\t5. Edit Students Info" << endl;
            cout << "\t\t\t\t\t6. view List of students" << endl;
            cout << "\t\t\t\t\t7. Back to main menu" << endl;
            cout << "\n\t\t\t\tYour choice : ";
            int choice;
            cin >> choice;
            system("cls");
            cin.ignore();
            switch (choice) {
                case 1:
                    addStudent();
                    break;
                case 2:
                      addLecturer();
                    break;
                case 3:
                   addDepartment();
                    break;
                case 4:
                    addCourseForDepartment();
                    break;
                case 5:
                      editStudentInformation();
                      break;
                 case 6:
                       seeListOfstudentBasedOnDepartmentYear();
                      break;
                case 7:
                    return;
                default:
                    cout << "Invalid choice" << endl;
            }
        }
    }
// This function demonstrates the use of linked lists for managing and sorting lecturer data by dynamically adding new lecturers to the list in sorted order. 
// Function to implement Bubble Sort on the linked list
void addLecturer() {
    ifstream read("lecturer.txt");
    string line;
    while (getline(read, line)) { 
        Admin* new_lecturer = new Admin; 
        new_lecturer->name = line;
        if (head == nullptr) {
            head = new_lecturer;
            head->next=nullptr;
            tail = new_lecturer;
            head->prev = nullptr;
            tail->next = nullptr;
            tail->prev = nullptr;

        } else {
            new_lecturer->prev = tail;
            tail->next = new_lecturer; 
            tail = new_lecturer; 
            tail->next = nullptr; 
        }
    }
    read.close();
    string new_lecturers, lecturerId;
    cout << "Enter your new lecturer name: (E.g Dr. Tewodros) ";
    getline(cin, new_lecturers);
    cout << "Enter lecturer id: ";
    getline(cin, lecturerId);
    string new_lecturerValue = "Name: " + new_lecturers + " Lecturer ID: " + lecturerId;
    Admin* new_added = new Admin;
    new_added->name = new_lecturerValue;

    // Add the new lecturer to the linked list
    if (tail != nullptr) {
        tail->next = new_added;
        new_added->prev = tail;
        tail = new_added;
    } else {
        head = tail = new_added;  // If the list is empty
    }
    tail->next = nullptr;

    // Apply Bubble Sort to sort the list by lecturer name
     if (head == nullptr) return;
    bool swapped;
    Admin* current;
    Admin* lastSorted = nullptr;

    do {
        swapped = false;
        current = head;

        // Traverse the list and swap adjacent nodes if they are out of order
        while (current->next != lastSorted) {
            if (current->name > current->next->name) {
                // Swap the data (names) between the nodes
                string temp = current->name;
                current->name = current->next->name;
                current->next->name = temp;
                swapped = true;
            }
            current = current->next;
        }
        lastSorted = current;

    } while (swapped);  // Continue until no more swaps are needed
    ofstream written("lecturer.txt");
    if (!written) {
        cout << "Error opening file for writing." << endl;
        return;
    }
  Admin*  writeToFile = head;
    while (writeToFile != nullptr) {
        written << writeToFile->name << endl;
        writeToFile = writeToFile->next;
    }
    written.close();

    cout << "Lecturer added in ascending order successfully." << endl;
    cout << "Press Enter to continue..." << endl;
    cin.get();

    // Ask the user for the next action
    int choice;
    cout << "1. See the list of the lecturers" << endl;
    cout << "2. Back to the main menu" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        system("cls");
        cout << "List of lecturers:" << endl << endl;
        Admin* showCurrent = head;
        while (showCurrent != nullptr) {
            cout << showCurrent->name << endl;
            showCurrent = showCurrent->next;
        }
        cout << "Press Enter to continue..." << endl;
        cin.get();
    }
    head=nullptr;
}


//this function adds students to a department file, ensuring that student records are sorted in ascending order based on their ID before saving. 
// It demonstrates the use of vectors for dynamic storage and file handling while ensuring the list remains ordered, which is a practical example of sorting in data structures.

 void addStudent() {
    system("cls");
    int batch;
    cout<<"\t\t\t\t\t0, for 2021-2022"<<endl;
    cout<<"\t\t\t\t\t1, for 2022-2023"<<endl;
    cout<<"\t\t\t\t\t2, for 2023-2024"<<endl;
    cout<<"\t\t\t\t\t3, for 2024-2025"<<endl;
    cout <<"\t\t\t\t\t\t\t Enter batch: ";
    cin >> batch;
    cin.ignore();
    vector<string> students;
    bool controller = false;
    bool control = false;
    string academicYear;
    switch (batch)
    {
    case 0:
        academicYear = "2021-2022";
        break;
    case 1:
        academicYear = "2022-2023";
        break;
    case 2:
        academicYear = "2023-2024";
        break;
    case 3:
        academicYear = "2024-2025";
        break;    
    default:
        cout << "Invalid choice" << endl;
        break;
    }
    string yearForId = academicYear.substr(2, 2);
    string student_id, full_name, department, gender;
    string line;
    int numberOfStudents = 0;

    do {
        system("cls");
        cout<<"\nEnter the correct information of the student---"<<endl<<endl;
        cout << "Enter full name: ";
        getline(cin, full_name);
        cout << "Enter department E.g computer science: ";
        getline(cin, department);
        cout << "Gender (male or female): ";
        getline(cin, gender);
        system("cls");
        cout<<"Here is the data you have entered"<<endl<<endl;
        cout<<"Full Name: "<<full_name<<endl;
        cout<<"Department: "<<department<<endl;
        cout<<"Gender: "<<gender<<endl;
        cout<<"Academic Year: "<<academicYear<<endl;
        cout<<"Do you want to add this student? (yes/no): ";
        string answer;
        getline(cin,answer);
        for(char &c :answer){
            c = tolower(c);
        }
        if (answer == "yes") {
            control = true;// if the control is true that alow the student is to be write.
        } else {
            control = false;
        }
        if(control){
        string filename = department + "_" + academicYear + ".txt";
        students.clear();
        ifstream read(filename);
        if (read) {
            getline(read, line);
            while (getline(read, line)) {
                students.push_back(line);
            }
            read.close();
            numberOfStudents = students.size() / 4;
        }     
        ofstream write(filename, ios::trunc);
        if (!write) {
            cerr << "Error: Unable to open the file for writing.\n";
            return;
        }
        write << "The number of students is: " << (numberOfStudents + 1) << endl;
        for (const auto &student : students) {
            write << student << endl;
        }
        write 
              << "Student ID: " << "UGR/" << numberOfStudents + 1 << "/" << yearForId << "\n"
              << "Full Name: " << full_name << "\n"
              << "Department: " << department << "\n"
              << "Gender: " << gender << endl;
        write.close();
        cout << "Student added successfully.\n";
           }

        cout << "Do you want to add more students?\n";
        cout << "1. Yes\n";
        cout << "2. No\n";
        int choice;
        cin >> choice;
        cin.ignore();
        controller = (choice == 1);

    } while (controller);
}


void addDepartment() {
    int stream;
    string depName;
    vector<string> lines;
    const string naturalSciences = "           ---------Natural Sciences---------";
    const string socialSciences = "           ---------Social Sciences----------";
    const string engineering = "           ----------Engineering-------------";
    const string arts = "           ----------Arts----------------";
    
    ifstream inputFile("Departments.txt");
    if (!inputFile) {
        ofstream initFile("Departments.txt");
        initFile << naturalSciences << endl;
        initFile << socialSciences << endl;
        initFile << engineering << endl;
        initFile << arts << endl;
        initFile.close();     
        addDepartment();
    } else {
        inputFile.clear(); 
        inputFile.seekg(0, ios::beg);
        
        string line;
        while (getline(inputFile, line)) {
            lines.push_back(line);
        }
        inputFile.close();
    }

    cout << "1, for Natural Sciences" << endl;
    cout << "2, for Social Sciences" << endl;
    cout << "3, for Engineering" << endl;
    cout << "4, for Arts" << endl;
    cout << "Enter the stream: ";
    cin >> stream;
    cin.ignore();
    cout << "Enter the name of the department in the format of (department of department name): ";
    getline(cin, depName);

    bool departmentAdded = false;

    switch (stream) {
        case 1: {
            auto it = find(lines.begin(), lines.end(), naturalSciences);
            if (it != lines.end()) {
                // Insert the new department below Natural Sciences
                lines.insert(it + 1, depName);
                departmentAdded = true;
            }
            break;
        }
        case 2: {
            auto it = find(lines.begin(), lines.end(), socialSciences);
            if (it != lines.end()) {
                lines.insert(it + 1, depName);
                departmentAdded = true;
            }
            break;
        }
        case 3: {
            auto it = find(lines.begin(), lines.end(), engineering);
            if (it != lines.end()) {
                lines.insert(it + 1, depName);
                departmentAdded = true;
            }
            break;
        }
        case 4: {
            auto it = find(lines.begin(), lines.end(), arts);
            if (it != lines.end()) {
                lines.insert(it + 1, depName);
                departmentAdded = true;
            }
            break;
        }
        default:
            cout << "Invalid choice" << endl;
            return;
    }

    if (!departmentAdded) {
        cerr << "Error: Unable to add the department. Stream header not found.\n";
        return;
    }
    ofstream outputFile("Departments.txt", ios::trunc);
    if (!outputFile) {
        cerr << "Error: Unable to open the file for writing.\n";
        return;
    }

    for (const auto& line : lines) {  // auto  automatic deduction for the type of the variable
        outputFile << line << endl;
    }
    outputFile.close();
    cout << "Department added successfully.\n";
}
// here is the problem .

void addCourseForDepartment() {
    int stream;
    string courseName,lecturerName,lecturerID,academicSemester;
    string courseCredit;
    string depChoice;
    vector<string> lines;
    const string naturalSciences = "           ---------Natural Sciences---------";
    const string socialSciences = "           ---------Social Sciences----------";
    const string engineering = "           ----------Engineering-------------";
    const string arts = "           ----------Arts----------------";
    cout << "1, for Natural Sciences" << endl;
    cout << "2, for Social Sciences" << endl;
    cout << "3, for Engineering" << endl;
    cout << "4, for Arts" << endl;
    cout << "Enter the stream: ";
    cin >> stream;
    cin.ignore(); 
    string selectedStream;
    switch (stream) {
        case 1: selectedStream = naturalSciences; break;
        case 2: selectedStream = socialSciences; break;
        case 3: selectedStream = engineering; break;
        case 4: selectedStream = arts; break;
        default:
            cout << "Invalid choice" << endl;
            return;
    }
    ifstream inputFile("Departments.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open Departments.txt for reading.\n";
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        lines.push_back(line);
    }
    inputFile.close();
    bool streamFound = false;
    vector<int> departmentPositions;
    for (size_t i = 0; i < lines.size(); ++i) {  // size_t for unsign integer value.
        if (lines[i] == selectedStream) {
            streamFound = true;
        } 
        else if (streamFound && lines[i].find("department of") != string::npos) {
             departmentPositions.push_back(i);
            if(lines[i+1]==socialSciences||lines[i+1]==naturalSciences||lines[i+1]==engineering||lines[i+1]==arts) {
                break;
            }
        } else if (streamFound && lines[i].empty()) {
            break; 
        }
    }

    if (departmentPositions.empty()) {
        cerr << "Error: No departments found under the selected stream.\n";
        return;
    }

    // Display departments and allow course addition
    for (size_t i = 0; i < departmentPositions.size(); ++i) {
        cout << i + 1 << ". " << lines[departmentPositions[i]] << endl;
    }

    cout << "Select a department by number to add courses: ";
    int departmentChoice;
    cin >> departmentChoice;
    cin.ignore(); // Clear buffer before getline.

    if (departmentChoice < 1 || departmentChoice > departmentPositions.size()) {
        cerr << "Invalid department choice.\n";
        return;
    }

    int selectedDepartmentIndex = departmentPositions[departmentChoice - 1];
    int insertPosition = selectedDepartmentIndex + 1;

    while (true) {
        cout << "Enter the name of the course: ";
        getline(cin, courseName);
        for(char &c :courseName){
            c=toupper(c);
        }
        cout << "Enter the credit hours of the course (e.g., '3' or '4'): ";
        getline(cin, courseCredit);
        cout << "Enter the name of the lecturer:(Dr. name) ";
        getline(cin, lecturerName);
        cout<<"Enter lecturer id: ";
        getline(cin,lecturerID);
        cout<<"Enter academic semester in this form(2024-semester1): ";
        getline(cin,academicSemester);
        
        // Create course entry
        string courseEntry ="---"+lecturerName+" "+lecturerID+" "+academicSemester+" " + courseName + " " + courseCredit + "Total(100%) Grade";
        lines.insert(lines.begin() + insertPosition, courseEntry);
        insertPosition++;

        cout << "Do you want to add another course (yes/no): ";
        getline(cin, depChoice);
        if (depChoice == "no") {
            break;
        }
    }

    ofstream outputFile("Departments.txt");
    if (!outputFile) {
        cerr << "Error: Unable to open Departments.txt for writing.\n";
        return;
    }

    for (const string& outputLine : lines) {
        outputFile << outputLine << endl;
    }
    outputFile.close();

    cout << "Courses added successfully under the selected department.\n";
}
// This function allows editing a student's information by searching for their ID in the department file, updating the details, and optionally deleting the student record. 
// It uses file manipulation to read, modify, and write student data, showcasing search, file handling, and conditional logic in the context of data structures.

void editStudentInformation() {
    string id, newName, newDepartment, academicYear,gender;
    cout << "Enter student ID to update their information: ";
    getline(cin, id);
    cout << "Enter his/her department: ";
    getline(cin, newDepartment);
    cout << "Enter academic year in this form (2024-2025): ";
    getline(cin, academicYear);

    for (char &ch : id) {
        ch = toupper(ch);
    }

    string formattedId = "Student ID: " + id;
    string filename = newDepartment + "_" + academicYear + ".txt";
    string tempFilename = "temp_" + filename;
    ifstream updateStudentsInformation(filename);
    if (!updateStudentsInformation) {
        cerr << "Error: Unable to open " << filename << " for reading.\n";
        return;
    }

    ofstream tempFile(tempFilename);
    if (!tempFile) {
        cerr << "Error: Unable to create temporary file.\n";
        return;
    }
    string line;
    bool allowtoWrite = true;
    bool found = false;
    int count = 0;
    while (getline(updateStudentsInformation, line)) {

        if(count>=0){
            allowtoWrite = true;
        }
        if (line.find(formattedId) != string::npos) {
        found = true;  
        cout<<"Do you want to delete this student? (yes/no to update his information): ";
        string choice;
        cin>>choice;
        cin.ignore();
        if(choice == "yes"){
            allowtoWrite = false;
            count = -4; 
            cout<<"Successfully deleted student\n";
        }
    else if(choice=="no"){
    cout << "Enter new name: ";
    getline(cin, newName);
      cout<<"Enter gender (male/female): ";
    getline(cin,gender);
       line = "Student ID: " + id + "\n" +"Full Name: " + newName + "\n" +"Department: " + newDepartment+"\n"+"Gender: "+gender ;
       tempFile << line << endl;
       allowtoWrite=false;
       count = -4; 
    }
    else {
        return;
    }
   
        }
        if(allowtoWrite){
        tempFile << line << endl;
    
    }
    count++;
    }

    if (!found) {
        cout << "No information found for Student ID: " << id << endl;
    } else {
        cout << "Student information updated successfully.\n";
    }
    updateStudentsInformation.close();
    tempFile.close();


    remove(filename.c_str());
    rename(tempFilename.c_str(), filename.c_str());
}
 struct Student {
    string studentID;
    string fullName;
    string department;
    string gender;
};

int partition(vector<Student>& students, int low, int high) {
    string pivot = students[high].fullName;
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (students[j].fullName < pivot) {
            ++i;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]);
    return i + 1;
}

// This code implements the Quick Sort algorithm to sort a list of students by their full name, using a vector to store student data. 
// The function parses student data from a file, sorts it using Quick Sort, and displays the sorted list based on department and academic year, demonstrating sorting techniques in data structures.

void quickSort(vector<Student>& students, int low, int high) {
    if (low < high) {
        int pi = partition(students, low, high);
        quickSort(students, low, pi - 1);
        quickSort(students, pi + 1, high);
    }
}
vector<Student> parseStudentData(ifstream& read) {
    vector<Student> students;
    string line, studentID, fullName, department, gender;
    while (getline(read, line)) {
        if (line.find("Student ID:") != string::npos) {
            studentID = line.substr(line.find(":") + 1);
        } else if (line.find("Full Name:") != string::npos) {
            fullName = line.substr(line.find(":") + 1);
        } else if (line.find("Department:") != string::npos) {
            department = line.substr(line.find(":") + 1);
        } else if (line.find("Gender:") != string::npos) {
            gender = line.substr(line.find(":") + 1);
            students.push_back({studentID, fullName, department, gender});
        }
    }
    return students;
}
void seeListOfstudentBasedOnDepartmentYear() {
    string department, academicYear;
    cout << "Enter department: ";
    getline(cin, department);
    cout << "Enter academic year in this form (2024-2025): ";
    getline(cin, academicYear);

    string filename = department + "_" + academicYear + ".txt";
    ifstream read(filename);
    if (!read) {
        cerr << "Error: Unable to open " << filename << " for reading.\n";
        return;
    }
    vector<Student> students = parseStudentData(read);
    read.close();

    if (students.empty()) {
        cout << "No students found in the file.\n";
        return;
    }
    quickSort(students, 0, students.size() - 1);
    system("cls");
    cout << "List of students in department " << department
         << " year " << academicYear << " (sorted by name):\n";
    for (const auto& student : students) {
        cout << "Name: " << student.fullName << ", ID: " << student.studentID << endl;
    }
    cin.get();
}
};  
Admin* Admin::head = nullptr;
Admin* Admin::tail = nullptr;
