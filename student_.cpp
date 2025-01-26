#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include<algorithm>
#include <ctime>
#include <vector>
using namespace std;

class Student {
private:
    string student_id;
    string department;
    string user_name;
    string password;
    double gpa;
    double cgpa;
    string full_name;
    string gender;
    string year;
    string semester;

public:
    void loginAsStudent() {
        cout << "Enter user name: ";
        cin >> user_name;
        cout << "Enter password: ";
        cin >> password;
        // Authentication logic can be added here.
    }
    void registerAsStudent();
    void courseRegistration();
    void viewProwrite();
    void viewCurrentSemesterInfo();
    void viewAllSemesterInfo();
};

class Lecturer {
private:
    string user_name;
    string password;

public:
    void loginAsLecturer() {
        cout << "Enter user name: ";
        cin >> user_name;
        cout << "Enter password: ";
        cin >> password;
        // Authentication logic can be added here.
    }
    void fillStudentGrade();
    void updateStudentGrade();
    void setUserNamePassword();
};
void addCourseForDepartment();
class Admin {
private:
    string user_name;
    string password;

public:
    void loginAsAdmin() {
        cout << "Enter user name: ";
        cin >> user_name;
        cout << "Enter password: ";
        cin >> password;
    }

    void adminMenu() {
        while (true) {
            cout << "\n\n\t\t\t\tWelcome to Admin Panel" << endl << endl;
            cout << "\t\t\t\t\t1. Add Student" << endl;
            cout << "\t\t\t\t\t2. Add Department" << endl;
            cout << "\t\t\t\t\t3. Add Course" << endl;
            cout << "\t\t\t\t\t4. Delete Student" << endl;
            cout << "\t\t\t\t\t5. Delete Course" << endl;
            cout << "\t\t\t\t\t6. View Students by Year" << endl;
            cout << "\t\t\t\t\t7. View Courses" << endl;
            cout << "\t\t\t\t\t8. Exit" << endl;
            cout << "\n\t\t\t\tYour choice? ";
            int choice;
            cin >> choice;
            cin.ignore();
            switch (choice) {
                case 1:
                    addStudent();
                    break;
                case 2:
                    addDepartment();
                    break;
                case 3:
                   addCourseForDepartment();
                    break;
                case 4:
                    deleteStudent();
                    break;
                case 5:
                    deleteCourse();
                    break;
                case 6:
                    viewStudentsByYear();
                    break;
                case 7:
                    viewCourses();
                    break;
                case 8:
                    return;
                default:
                    cout << "Invalid choice" << endl;
            }
        }
    }
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
        cout<<"\n--------------Enter the correct information of the student------------"<<endl;
        cout << "Enter full name: ";
        getline(cin, full_name);
        cout << "Enter department: ";
        getline(cin, department);
        cout << "Gender (male or female): ";
        getline(cin, gender);
        cout<<"Here is the data you have entered"<<endl;
        cout<<"Full Name: "<<full_name<<endl;
        cout<<"Department: "<<department<<endl;
        cout<<"Gender: "<<gender<<endl;
        cout<<"Academic Year: "<<academicYear<<endl;
        cout<<"Year for ID: "<<"UGR/"<<numberOfStudents+1<<"/"<<yearForId<<endl;
        cout<<"Do you want to add this student? (yes/no): ";
        string answer;
        getline(cin,answer);
        for(char &c :answer){
            c = tolower(c);
        }
        if (answer == "yes") {
            control = true;
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
        write << "Full Name: " << full_name << "\n"
              << "Student ID: " << "UGR/" << numberOfStudents + 1 << "/" << yearForId << "\n"
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
    
    // Check if the file exists and is empty
    ifstream inputFile("Departments.txt");
    if (!inputFile) {
        // File does not exist, create it and add headers
        ofstream initFile("Departments.txt");
        initFile << naturalSciences << endl;
        initFile << socialSciences << endl;
        initFile << engineering << endl;
        initFile << arts << endl;
        initFile.close();
    } else {
        inputFile.clear(); 
        inputFile.seekg(0, ios::beg);
        
        // Read existing lines
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
    cout << "Enter the name of the department: ";
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
                // Insert the new department below Social Sciences
                lines.insert(it + 1, depName);
                departmentAdded = true;
            }
            break;
        }
        case 3: {
            auto it = find(lines.begin(), lines.end(), engineering);
            if (it != lines.end()) {
                // Insert the new department below Engineering
                lines.insert(it + 1, depName);
                departmentAdded = true;
            }
            break;
        }
        case 4: {
            auto it = find(lines.begin(), lines.end(), arts);
            if (it != lines.end()) {
                // Insert the new department below Arts
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

    // Write the updated lines back to the file
    ofstream outputFile("Departments.txt", ios::trunc);
    if (!outputFile) {
        cerr << "Error: Unable to open the file for writing.\n";
        return;
    }
    for (const auto& line : lines) {
        outputFile << line << endl;
    }
    outputFile.close();

    cout << "Department added successfully.\n";
}
void addcourseForDepartment() {


}

    void deleteStudent() {
        string id;
        cout << "Enter student ID to delete: ";
        cin >> id;

        ifstream write("students.txt");
        ofstream temp("temp.txt");

        string student_id, full_name, department;
        bool found = false;

        while (write >> student_id >> full_name >> department) {
            if (student_id != id) {
                temp << student_id << " " << full_name << " " << department << endl;
            } else {
                found = true;
            }
        }

        write.close();
        temp.close();

        remove("students.txt");
        rename("temp.txt", "students.txt");

        if (found) {
            cout << "Student deleted successfully." << endl;
        } else {
            cout << "Student not found." << endl;
        }
    }

    void deleteCourse() {
        string id;
        cout << "Enter course ID to delete: ";
        cin >> id;

        ifstream write("courses.txt");
        ofstream temp("temp.txt");

        string course_id, course_name;
        int course_credit;
        bool found = false;

        while (write >> course_id >> course_name >> course_credit) {
            if (course_id != id) {
                temp << course_id << " " << course_name << " " << course_credit << endl;
            } else {
                found = true;
            }
        }

        write.close();
        temp.close();

        remove("courses.txt");
        rename("temp.txt", "courses.txt");

        if (found) {
            cout << "Course deleted successfully." << endl;
        } else {
            cout << "Course not found." << endl;
        }
    }

    void viewStudentsByYear() {
        cout << "Feature not implemented yet." << endl;
    }

    void viewCourses() {
        ifstream write("courses.txt");
        string course_id, course_name;
        int course_credit;

        while (write >> course_id >> course_name >> course_credit) {
            cout << "Course ID: " << course_id << endl;
            cout << "Course Name: " << course_name << endl;
            cout << "Course Credit: " << course_credit << endl;
            cout << "-------------------------" << endl;
        }
        write.close();
    }
};

void loginOptions() {
    while (true) {
        cout << "\n\n\t\t\t\tWelcome to Student Management System" << endl << endl;
        cout << "\t\t\t\t\t1. Login as Student" << endl;
        cout << "\t\t\t\t\t2. Login as Lecturer" << endl;
        cout << "\t\t\t\t\t3. Login as Admin" << endl;
        cout << "\t\t\t\t\t4. Exit" << endl;
        cout << "\t\t\t\t\tYour choice ? ";
        int choice;
        cin >> choice;

        Student student;
        Lecturer lecturer;
        Admin admin;

        switch (choice) {
            case 1:
                student.loginAsStudent();
                break;
            case 2:
                lecturer.loginAsLecturer();
                break;
            case 3:
                admin.loginAsAdmin();
                admin.adminMenu();
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice." << endl;
        }
    }
}

int main() {
    system("cls"); 
    loginOptions();
    return 0;
}
