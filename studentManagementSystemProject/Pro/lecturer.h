
#include"header.h"
void loginOptions();    
class Lecturer {
private:
    string user_name;
    string password;

public:
// The algorithm reads the lecturer data into a vector and performs a binary search to quickly find the corresponding login entry,
// making it a space-efficient and time-efficient solution for handling large numbers of lecturer records.
    void loginAsLecturer() {
        system("cls");      
        cout << "\n\t\tEnter user name (Dr. your_name): ";
        getline(cin, user_name);
        cout << "\t\tEnter password: ";
        getline(cin, password);
        system("cls");
        vector<string> lines;
        string line;
        string loginData = "Name: " + user_name + " Lecturer ID: " + password;
        ifstream loginLecturer("lecturer.txt");
        while (getline(loginLecturer, line)) {
            lines.push_back(line);
        }
        loginLecturer.close();

        int left = 0, right = lines.size() - 1;
        bool found = false;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (lines[mid] == loginData) {
                found = true;
                break;
            } else if (lines[mid] < loginData) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        if (found) {
            cout << "Login successful" << endl;
            lecturerMenu();
        } else {
            cout << "\t\t\t\t\tLogin failed" << endl;
            cin.get();
            loginOptions();
        }
    }

    void lecturerMenu() {
        while (true) {
           system("cls");
            cout<<GREEN<<endl;
            cout << "\n\n\t\t\t\tWelcome to Lecturer Management System\n\n";
            cout << "\t\t\t\t\t1. Fill student grade\n";
            cout << "\t\t\t\t\t2. Update student grade\n";
            cout << "\t\t\t\t\t3. Back to main menu\n";
            cout << "\t\t\t\t\t4. Exit\n";
            cout << "\t\t\t\t\t   Your choice: ";

            int choice;
            cin >> choice;
            cin.ignore();
            system("cls");
            switch (choice) {
                case 1:
                    fillStudentGrade();
                    break;
                case 2:
                    fillStudentGrade();
                    break;
                case 3:
                    return; 
                case 4:
                    exit(0); 
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        }
    }

// The function uses a linear search to find the student's record by student ID and then performs string operations to
// update the student's grade. It handles file management efficiently by using temporary files, demonstrating key operations 
// in file I/O and string manipulation in DSA.
void fillStudentGrade() {
    system("cls");
      string idForFile, student_id, line3, course_name;
      cout << "Enter student ID: ";
      getline(  cin, student_id);
      for(int i=0; i< student_id.length(); i++){
        if(student_id[i]!='/'){
            idForFile+=student_id[i];
        }
      }
      ifstream grading(idForFile + ".txt");
    if (!grading) {
          cerr << "Error opening file for reading." <<   endl;
        return;
    }
    bool founded = false;
    while (  getline(grading, line3)) {
        if (line3 == "studentId: " + student_id) {
            founded = true;
            break;
        }
    }
    grading.close();
      string line4;
      ofstream temp("temp.txt",   ios::app);
    if (!temp) {
          cerr << "Error opening temporary file for writing." <<   endl;
        return;
    }
    if (founded) {
        system("cls");
          cout << "Enter course name: ";
          getline(  cin, course_name);
        for (char &c : course_name) {
            c = toupper(c);
        }
          ifstream grade(idForFile + ".txt");
        if (!grade) {
              cerr << "Error opening file for reading." <<   endl;
            return;
        }

        while (  getline(grade, line4)) {
            size_t position = line4.find(course_name);

            if (position !=   string::npos) {
                size_t position5 = line4.find("Total(100%)");
                  string position1 = line4.substr(0,position5+12);
                float score;

                  cout << "Enter the student result from (100%): ";
                  cin >> score;
                  cin.ignore();
                
                char grade;
                if (score >= 80) {
                    grade = 'A';
                } else if (score >= 70) {
                    grade = 'B';
                } else if (score >= 50) {
                    grade = 'C';
                } else {
                    grade = 'D';
                }

                string scores =   to_string(score);
                line4 = position1 + scores + " Grade " + grade;
            }
            temp << line4 <<   endl;
        }

        grade.close();
    }
    temp.close();
    if (remove((idForFile + ".txt").c_str()) != 0) {
          cerr << "Error deleting original file." <<   endl;
    }
    if (rename("temp.txt", (idForFile + ".txt").c_str()) != 0) {
          cerr << "Error renaming temporary file." <<   endl;
    }
}
};