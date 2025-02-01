#include"header.h"
#include"admin.h"
#include"student.h"
#include"lecturer.h"
void loginOptions() {
    while (true) {
        system("cls");
        cout<<GREEN<<endl;
        cout << "\n\n\t\t\t\tWelcome to Student Management System" << endl;
        cout<<RESET;
        cout<<MAGENTA<<endl;
        cout << "\t\t\t\t\t1. Login as Admin" << endl;
        cout << "\t\t\t\t\t2. Login as Lecturer" << endl;
        cout << "\t\t\t\t\t3. Login as Student" << endl;
        cout << "\t\t\t\t\t4. Exit" << endl;
        cout << "\t\t\t\t\tYour choice : ";
        int choice;
        cout<<RESET;
        cout<<GREEN;
        cin >> choice;
        cin.ignore();
        Student student;
        Lecturer lecturer;
        Admin admin;

        switch (choice) {
            case 3:
                student.loginAsStudent();
                break;
            case 2:
                lecturer.loginAsLecturer();
                lecturer.lecturerMenu();
                break;
            case 1:
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
