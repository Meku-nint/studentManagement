#include"header.h"
using namespace std;

class Student {
private:
    string student_id;
    string department;
    string user_name;
    string password;
    double gpa;
    string full_name;
    string year;
    string year_semester;

    // that 

public:
// The function demonstrates file handling and string manipulation to search for student credentials. It utilizes a binary
// search on the list of student IDs, ensuring a time-efficient login verification process even for larger files with sorted data.

    void loginAsStudent() {
        system("cls");
        cout << "Enter studentId in the form of (UGR/2/24) ";
        getline(cin, student_id);
        for (char& c : student_id) {
            c = toupper(c);
        }
        student_id = "Student ID: " + student_id;

        cout << "Enter department ( department name E.g computer science): ";
        getline(cin, department);
        int batch;
        cout << "\t\t\t\t\t0, for 2021-2022" << endl;
        cout << "\t\t\t\t\t1, for 2022-2023" << endl;
        cout << "\t\t\t\t\t2, for 2023-2024" << endl;
        cout << "\t\t\t\t\t3, for 2024-2025" << endl;
        cout << "\t\t\t\t\t\t\t Enter batch: ";
        cin >> batch;
        cin.ignore();
        switch (batch) {
            case 0:
                year = "2021-2022";
                break;
            case 1:
                year = "2022-2023";
                break;
            case 2:
                year = "2023-2024";
                break;
            case 3:
                year = "2024-2025";
                break;
            default:
                cout << "invalid input" << endl;
                return;
        }
        system("cls");
        string filename = department + "_" + year + ".txt";
        ifstream loginStudent(filename);

        if (!loginStudent) {
            cerr << "Error: Unable to open " << filename << " for reading.\n";
            cin.get();
            return;
        }

        string line;
        vector<string> listOfId;
        int studentCount = 0;
        while (getline(loginStudent, line)) {
            if (line.rfind("Student ID: ", 0) == 0) {
                listOfId.push_back(line);
                studentCount++;
            }
        }
        loginStudent.close();
        if (listOfId.empty()) {
            cerr << "Error: No student IDs found in the file.\n";
            cin.get();
            return;
        }
        int left = 0, right = studentCount - 1;
        bool found = false;
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (listOfId[mid] == student_id) {
                found = true;
                break;
            } else if (listOfId[mid] < student_id) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // Display results
        if (found) {
            cout << "\t\t\tLogin successful\n";
            cout<<"\t\tclick enter to continue to student menu \n";
            cin.get();
            studentMenu();
        } else {
            cout << "Invalid studentId or password.\n";
            cin.get();
        }
    }
    // We use a linear search (O(n)) to find the semester data in the file since the dataset is small, making it efficient in this case.  
// The credit hour and grade are extracted using string manipulation, mimicking key-value retrieval in an unordered list.

void calculateGpa() {
    int totalCreditHours = 0;
    double gradePoints = 0;
    string studentId;
    system("cls");
    cout << "Enter Your Student ID: ";
    getline(cin,studentId);
    string nameForFile;
    for(int i=0;i<studentId.length();i++){
        if(studentId[i]!='/'){
            nameForFile+=studentId[i];
        }
    }
    cout << "Enter academic semester and year in the format (2024-semester1): ";
    getline(cin, year_semester);

    cout << "How many courses do you take: ";
    int courseCount;
    cin >> courseCount;
    cin.ignore(); 

    ifstream gpaCalculate(nameForFile + ".txt");
    if (!gpaCalculate) {
        cout << "Error opening file." << endl;
        return;
    }
    ofstream temp("temp.txt");
    string line;
    bool written=false;
    while (getline(gpaCalculate, line)) {
        size_t position = line.find(year_semester);
        if (position != string::npos) {
            size_t position1 = line.find("Total");
            string creditHourStr = line.substr(position1 - 1, 1); 
            size_t position2 = line.find("Grade ");
            char grade = line.substr(position2 + 6, 1)[0];

            int creditHour = stoi(creditHourStr);
            int gradeValue;
            switch (grade) {
                case 'A': gradeValue = 4; break;
                case 'B': gradeValue = 3; break;
                case 'C': gradeValue = 2; break;
                case 'D': gradeValue = 1; break;
                default: gradeValue = 0; break;
            }

            totalCreditHours += creditHour;
            gradePoints += gradeValue * creditHour;

            courseCount--;
            temp << line << endl;
            written=true;
        }

        if (courseCount == 0) {
            if (totalCreditHours != 0) {
                gpa = gradePoints / totalCreditHours;
                temp << fixed << setprecision(2) << "GPA: " << gpa << endl;
            }
        }
        if(!written){
        temp << line << endl;

        }

    }

    temp.close();
    gpaCalculate.close();
    remove((full_name + ".txt").c_str());
    rename("temp.txt", (full_name + ".txt").c_str());

    cout << "GPA  "<<gpa<<"  completed and saved." << endl;
    cin.get();
}

    void courseRegistration() {
        system("cls");
        cout << "\n\n\t\t\t\tWelcome to Course Registration\n\n";
        cout << "Enter Acc year and semester: in the format(2024-semester1)";
        getline(cin, year_semester);
        cout<<"Enter your id ,E.g if your id is(ugr/2/24)->you have to enter in the format (ugr224) : ";
        getline(cin, student_id);
        cout << "Enter department name in the format(department of dep_name):";
        getline(cin, department);
        ifstream courseFile("Departments.txt");
        string line, temp;
        bool found = false;
        vector<string> courseList;
        while (getline(courseFile, line)) {
            if (line == department) {
                found = true;
                cout << "\t\tHere is the list of courses for " << department << "    " << year_semester << endl << endl;
            }
            if (found) {
                system("cls");
                size_t threeHyphen = line.find("---");
                size_t position = line.find(year_semester);
                if (position != string::npos && threeHyphen != string::npos) {
                    courseList.push_back(line.substr(position));
                }
            }
        }
        courseFile.close();
        if (!found) {
            cout << "Invalid department name";
        } else {
            for (int i = 0; i < courseList.size(); i++) {
                cout << i + 1 << ". " << courseList[i] << endl;
            }
            cout << "Register for all these courses?(yes/no for registration each by each): ";
            getline(cin, temp);
            if (temp == "yes") {
                ofstream studentInfo(student_id + ".txt",ios::app);

                system("cls");
                for (int i = 0; i < courseList.size(); i++) {
                    studentInfo << courseList[i] << endl;
                }
                studentInfo.close();
                cout << "You have successfully registered for all the courses";
            } else if (temp == "no") {
                system("cls");
                for (int i = 0; i < courseList.size(); i++) {
                    cout << i + 1 << ". " << courseList[i] << endl;
                    cout << "Do you want register for this course (yes/no): ";
                    getline(cin, temp);
                    if(temp=="yes"){
                        ofstream studentInfo(student_id + ".txt",ios::app);
                        studentInfo << courseList[i] << endl;
                        studentInfo.close();
                        cout << "You have successfully registered for " << courseList[i] << endl;
                    }
                }
            }
        }
    }
// This program utilizes **file handling** and **sequential search** because the data set is too small and un sorted to manage course registration. 
// The program also performs **string matching** using `find()`, which operates in **O(m*n)** in the worst case.

    void viewCurrentSemesterInfo() {
         system("cls");
        string line,line2;
        cout<<"Enter semester in the format (2024-semester1)";
        getline(cin, year_semester);
        cout<<"Enter full_name ";
        getline(cin, full_name);
        cout<<"Enter password : ";
        getline(cin, password);
         system("cls");
        password="Password: "+password;
        bool founded=false;
        ifstream semesterInfo(full_name + ".txt");
        while(getline(semesterInfo, line2)){
            if(line2==password){
                founded=true;
        }
        }
        if(!founded){
            cout<<"Invalid password";
            cin.get();
            studentMenu();
        }
        while(getline(semesterInfo, line)){
            size_t position = line.find(year_semester);
                if (position != string::npos ) {
                    cout<<line<<endl;
                }
        }
        semesterInfo.close();
        cin.get();
    studentMenu();
    }

    void viewAllSemesterInfo() {
        system("cls");
        string line,line2;
        cout<<"Enter full_name ";
        getline(cin, full_name);
        cout<<"Enter password : ";
        getline(cin, password);
        password="Password: "+password;
        bool founded=false;
        ifstream allSemesterInfo(full_name + ".txt");
        while(getline(allSemesterInfo, line2)){
            if(password==line2){
                founded=true;
                break;
        }
        }
        if(!founded){
            cout<<"Invalid password";
            cin.get();
            studentMenu();
        }

        while(getline(allSemesterInfo, line)){
            size_t position = line.find("semester");
                if (position != string::npos ) {
                    cout<<line<<endl;
                }
        }
        allSemesterInfo.close();
        cin.get();
    studentMenu();
    }
    
   void createOwnStudentAccount() {
       system("cls");
       cout << "Enter department name in the format(department of dep_name):";
       getline(cin, department);
       cout << "Enter your batch in the format of(2021-2022)";
       getline(cin, year_semester);
       cout<<"Enter studentId ";
       getline(cin, student_id);
       cout<<"Enter some password ";
       string fileName;
       for(int i=0;i<student_id.length();i++){
          if(student_id[i]!='/'){
            fileName+=student_id[i];
          }
       }
       getline(cin,password);
       ofstream studentInfo(fileName + ".txt");
       studentInfo << "Department: " << department << endl;
       studentInfo << "Acc year : " << year_semester << endl;
       studentInfo << "Password: " << password << endl;
       studentInfo << "studentId: " << student_id << endl;
       studentInfo.close();
       system("cls");
       cout << "You have successfully created your own student account";
       cin.get();
   }
    void studentMenu() {
        system("cls");
        cout << "\n\n\t\t\t\tWelcome to Student Management System\n\n";
        cout << "\t\t\t\t0. Create own student account\n";
        cout << "\t\t\t\t1. Course Registration\n";
        cout << "\t\t\t\t2. View Current Semester Info\n";
        cout << "\t\t\t\t3. View All Semester Info\n";
        cout<<  "\t\t\t\t4. View your GPA \n";
        cout << "\t\t\t\t5. back to main menu\n";
        cout<<  "\t\t\t\t6. Exit\n";
        cout << "\t\t\t\t\t\tYour choice: ";
        int choice;
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 0:
            createOwnStudentAccount();
            break;
            case 1:
                courseRegistration();
                break;
            case 2:
                viewCurrentSemesterInfo();
                break;
            case 3:
                viewAllSemesterInfo();
                break;
            case 4:
                  calculateGpa();
                  break;
            case 5:
                return ;
                  break;
            case 6:
                exit(0);
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
};
