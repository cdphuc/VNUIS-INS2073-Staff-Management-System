#include "conio.h"
#include "iostream"
#include "string"
#include "vector"
#include "map"
#include "fstream"
#include "set"

using namespace std;

class Schedule {
private:
    int scheduleID;
    string startTime;
    string endTime;
public:
    Schedule(int scheduleID, string startTime, string endTime) {
        this->scheduleID = scheduleID;
        this->startTime = startTime;
        this->endTime = endTime;
    }

    int getScheduleID() const {
        return scheduleID;
    }

    string getStartTime() const {
        return startTime;
    }

    string getEndTime() const {
        return endTime;
    }
};

class Department; //forward declaration

set<int> usedEmployeeIDs;

class Employee {
private:
    string employeeID, employeeName, dateOfBirth;
    double salary;
    Schedule *schedule;
    Department *department;
    static int employeeCount;
public:
    Employee() = default; //Employee default constructor
    Employee(string employeeID, string employeeName, string dateOfBirth, double salary) {
        this->employeeID = employeeID;
        this->employeeName = employeeName;
        this->dateOfBirth = dateOfBirth;
        this->salary = salary;
    }

    string getEmployeeID() const {
        return employeeID;  //get employee ID
    }

    string getEmployeeName() const { //get employee name
        return employeeName;
    }

    string getDateOfBirth() const { //get employee birthday
        return dateOfBirth;
    }

    double getSalary() const { //get employee salary
        return salary;
    }

    void setSalary(const double &salary) { //set employee salary
        this->salary = salary;
    }

    Schedule *getSchedule() const { //get employee schedule
        return schedule;
    }

    void setEmployeeName(const string &employeeName) { //set employee name
        this->employeeName = employeeName;
    }

    void setDateOfBirth(const string &dateOfBirth) { //set employee birthday
        this->dateOfBirth = dateOfBirth;
    }

    void setSchedule(Schedule *schedule) { //set employee schedule
        this->schedule = schedule;
    }

    void setDepartment(Department *department) { //set employee department
        this->department = department;
    }

    Department *getDepartment() const { //get employee department
        return department;
    }

    static int getEmployeeCount() { //get employee count
        return employeeCount;
    }

    static void setEmployeeCount(int employeeCount) { //set employee count
        Employee::employeeCount = employeeCount;
    }

    void inputEmployee() { //enter employee from keyboard
        int newEmployeeID = 1;
        while (usedEmployeeIDs.find(newEmployeeID) != usedEmployeeIDs.end()) {
            newEmployeeID++;
        }
        usedEmployeeIDs.insert(newEmployeeID);
        this->employeeID = "E" + string(3 - to_string(newEmployeeID).length(), '0') + to_string(newEmployeeID);
        cout << "Enter employee name: ";
        getline(cin, this->employeeName);
        cout << "Enter date of birth: ";
        cin >> this->dateOfBirth;
        cout << "Enter salary: ";
        cin >> this->salary;
        cin.ignore();
    }

    void displayEmployeeDetails() const {
        cout << "Employee ID: " << employeeID << endl;
        cout << "Employee Name: " << employeeName << endl;
        cout << "Date of Birth: " << dateOfBirth << endl;
        cout << "Salary: " << salary << endl;
        if (schedule) {
            cout << "Schedule ID: " << schedule->getScheduleID() << endl;
            cout << "Start Time: " << schedule->getStartTime() << endl;
            cout << "End Time: " << schedule->getEndTime() << endl;
        }
    }

};

int Employee::employeeCount = 0;

class Department {
private:
    string departmentID, departmentName, location;
    vector<Employee *> employees;
public:
    Department() = default; //Department default constructor
    Department(string departmentID, string departmentName, string location) {
        this->departmentID = departmentID;
        this->departmentName = departmentName;
        this->location = location;
    }

    string getDepartmentID() const {
        return departmentID;
    }

    string getDepartmentName() const {
        return departmentName;
    }

    string getLocation() const {
        return location;
    }

    vector<Employee *> getEmployees() const {
        return employees;
    }

    void addEmployee(Employee *employee) {
        employees.push_back(employee);
        employee->setDepartment(this);
    }

    void deleteEmployee(const string &employeeID) {
        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if ((*it)->getEmployeeID() == employeeID) {
                employees.erase(it);
                break;
            }
        }
    }

    void displayDepartmentDetails() {
        cout << "Department ID: " << departmentID << endl;
        cout << "Department Name: " << departmentName << endl;
        cout << "Location: " << location << endl << endl;
        cout << "Employees: " << endl;
        for (auto &employee: employees) {
            employee->displayEmployeeDetails();
            cout << endl;
        }
    }
};

map<int, Schedule *> schedules;
multimap<int, Employee *> employeesBySchedule;

void createSchedules() {
    schedules[1] = new Schedule(1, "08:00", "16:00");
    schedules[2] = new Schedule(2, "09:00", "17:00");
    schedules[3] = new Schedule(3, "10:00", "18:00");
}

void createEmployeeMenu(Department &Sales, Department &Technology, Department &Finance) {
    int numEmployees, successCreation;
    cout << "Enter the number of employee(s): ";
    cin >> numEmployees;
    cin.ignore();
    successCreation = numEmployees;
    for (int i = 0; i < numEmployees; i++) {
        cout << endl;
        cout << "Enter details for employee " << i + 1 << endl;
        auto *emp = new Employee();
        emp->inputEmployee();
        int scheduleID;
        cout << "Available schedules: " << endl;
        for (auto &schedule: schedules) {
            cout << "Schedule ID: " << schedule.first << " Start Time: " << schedule.second->getStartTime()
                 << " End Time: " << schedule.second->getEndTime() << endl;
        }
        cout << "Enter schedule ID: ";
        cin >> scheduleID;
        cin.ignore();
        if (schedules.find(scheduleID) != schedules.end()) {
            emp->setSchedule(schedules[scheduleID]);
            employeesBySchedule.insert(make_pair(scheduleID, emp));
        } else {
            cout << "Employee creation failed. Invalid schedule ID." << endl;
            delete emp;
            successCreation--;
            continue;
        }
        string departmentChoice;
        cout << "Enter the department (Sales/Technology/Finance): ";
        getline(cin, departmentChoice);
        if (departmentChoice == "Sales") {
            Sales.addEmployee(emp);
            cout << "Employee created successfully." << endl;
        } else if (departmentChoice == "Technology") {
            Technology.addEmployee(emp);
            cout << "Employee created successfully." << endl;
        } else if (departmentChoice == "Finance") {
            Finance.addEmployee(emp);
            cout << "Employee created successfully." << endl;
        } else {
            cout << "Employee creation failed. No department available." << endl;
            delete emp;
            successCreation--;
        }
    }
    cout << "Successfully created " << successCreation << "/" << numEmployees << " employee(s)." << endl;
    getch();
    system("cls");
}

void displayDepartmentsMenu(Department &Sales, Department &Technology, Department &Finance) {
    int choice;
    do {
        cout << "1. Display sales department." << endl;
        cout << "2. Display technology department." << endl;
        cout << "3. Display finance department." << endl;
        cout << "4. Display all department." << endl;
        cout << "5. Back to main menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                system("cls");
                Sales.displayDepartmentDetails();
                getch();
                system("cls");
                break;
            case 2:
                system("cls");
                Technology.displayDepartmentDetails();
                getch();
                system("cls");
                break;
            case 3:
                system("cls");
                Finance.displayDepartmentDetails();
                getch();
                system("cls");
                break;
            case 4:
                system("cls");
                Sales.displayDepartmentDetails();
                cout << endl;
                Technology.displayDepartmentDetails();
                cout << endl;
                Finance.displayDepartmentDetails();
                getch();
                system("cls");
                break;
            case 5:
                system("cls");
                break;
            default:
                cout << "Invalid choice. Please try again..." << endl;
                getch();
                system("cls");
        }
    } while (choice != 5);
}


Department *findDepartmentByName(const string &departmentName, vector<Department *> &departments) {
    for (auto department: departments) {
        if (department->getDepartmentName() == departmentName) {
            return department;
        }
    }
    return nullptr;
}

Employee *findEmployeeByID(const string &employeeID, Department *department) {
    for (auto employee: department->getEmployees()) {
        if (employee->getEmployeeID() == employeeID) {
            return employee;
        }
    }
    return nullptr;
}

void updateEmployeeByID(vector<Department *> &departments) {
    cout << "Enter the department that needs to update employee information (Sales/Technology/Finance): ";
    string departmentName;
    getline(cin, departmentName);

    Department *department = findDepartmentByName(departmentName, departments);
    if (!department) {
        cout << "Department not found!" << endl;
        return;
    } else {
        if (department->getEmployees().empty()) {
            cout << "No employees found in this department." << endl;
            return;
        } else {
            department->displayDepartmentDetails();
        }
    }

    cout << "Enter the employee ID to update: ";
    string employeeID;
    cin >> employeeID;
    cin.ignore();

    Employee *employee = findEmployeeByID(employeeID, department);
    if (employee) {
        cout << "Enter new employee name: ";
        string newEmployeeName;
        getline(cin, newEmployeeName);
        employee->setEmployeeName(newEmployeeName);

        cout << "Enter new date of birth: ";
        string newDateOfBirth;
        cin >> newDateOfBirth;
        employee->setDateOfBirth(newDateOfBirth);
        cout << "Enter new salary: ";

        double newSalary;
        cin >> newSalary;
        employee->setSalary(newSalary);
        cin.ignore();

        cout << "Employee updated successfully." << endl;
    }
}

void updateEmployeeSchedule(vector<Department *> &departments) {
    cout << "Enter the department that needs to update employee schedule (Sales/Technology/Finance): ";
    string departmentName;
    getline(cin, departmentName);
    Department *department = findDepartmentByName(departmentName, departments);
    if (!department) {
        cout << "Department not found!" << endl;
        return;
    } else {
        if (department->getEmployees().empty()) {
            cout << "No employees found in this department." << endl;
            return;
        } else {
            department->displayDepartmentDetails();
        }
    }
    cout << "Enter the employee ID to update schedule: ";
    string employeeID;
    cin >> employeeID;
    cin.ignore();
    Employee *employee = findEmployeeByID(employeeID, department);
    if (employee) {
        int newScheduleID;
        cout << "Available schedules: " << endl;
        for (auto &schedule: schedules) {
            cout << "Schedule ID: " << schedule.first << " Start Time: " << schedule.second->getStartTime()
                 << " End Time: " << schedule.second->getEndTime() << endl;
        }
        bool validScheduleID = false;
        while (!validScheduleID) {
            cout << "Enter new schedule ID: ";
            cin >> newScheduleID;
            cin.ignore();
            if (schedules.find(newScheduleID) != schedules.end()) {
                for (auto it = employeesBySchedule.begin(); it != employeesBySchedule.end(); ++it) {
                    if (it->second == employee) {
                        employeesBySchedule.erase(it);
                        break;
                    }
                }
                employee->setSchedule(schedules[newScheduleID]); //Update employee schedule
                employeesBySchedule.insert(
                        make_pair(newScheduleID, employee)); //Add the new entry to the employeesBySchedule map
                cout << "Employee updated successfully." << endl;
                validScheduleID = true;
            } else {
                cout << "Invalid schedule ID. Please try again." << endl;
            }
        }
    }
}


void updateEmployeeDepartment(vector<Department *> &departments) {
    for (auto department: departments) {
        department->displayDepartmentDetails();
    }
    cout << "Enter the employee ID to change department: ";
    string employeeID;
    cin >> employeeID;
    cin.ignore();

    Department *currentDepartment = nullptr;
    Employee *employee = nullptr;
    for (auto department: departments) {
        employee = findEmployeeByID(employeeID, department);
        if (employee) {
            currentDepartment = department;
            break;
        }
    }

    if (!employee) {
        cout << "Employee not found." << endl;
        return;
    }

    cout << "Enter the new department name (Sale/Technology/Finance): ";
    string newDepartmentName;
    getline(cin, newDepartmentName);

    Department *newDepartment = findDepartmentByName(newDepartmentName, departments);
    if (!newDepartment) {
        cout << "Department not found." << endl;
        return;
    }

    currentDepartment->deleteEmployee(employeeID);
    newDepartment->addEmployee(employee);
    cout << "Employee department changed successfully." << endl;
}

void deleteEmployeeFromDepartment(vector<Department *> &departments) {
    cout << "Enter the name of the department that employee to be deleted (Sales/Technology/Finance): ";
    string departmentName;
    getline(cin, departmentName);
    Department *department = findDepartmentByName(departmentName, departments);
    if (!department) {
        cout << "Department not found." << endl;
        return;
    } else {
        if (department->getEmployees().empty()) {
            cout << "No employees found in this department." << endl;
            return;
        } else {
            department->displayDepartmentDetails();
        }
    }
    cout << "Enter the employee ID to delete: ";
    string employeeID;
    cin >> employeeID;
    cin.ignore();
    Employee *employee = findEmployeeByID(employeeID, department);
    if (employee) {
        department->deleteEmployee(employeeID);
        usedEmployeeIDs.erase(stoi(employee->getEmployeeID().substr(1)));
        cout << "Employee deleted successfully." << endl;
        getch();
        system("cls");
    } else {
        cout << "Employee not found." << endl;
        getch();
        system("cls");
    }
}

void searchEmployeeByID(vector<Department *> &departments) {
    cout << "Enter the employee ID to search: ";
    string employeeID;
    cin >> employeeID;
    cin.ignore();
    cout << endl;

    Department *employeeDepartment = nullptr;
    Employee *employee = nullptr;
    for (auto department: departments) {
        employee = findEmployeeByID(employeeID, department);
        if (employee) {
            employeeDepartment = department;
            break;
        }
    }
    if (employee) {
        cout << "Employee name: " << employee->getEmployeeName() << endl;
        cout << "Date of birth: " << employee->getDateOfBirth() << endl;
        cout << "Salary: " << employee->getSalary() << endl;
        cout << "Department ID: " << employeeDepartment->getDepartmentID() << endl;
        cout << "Department: " << employeeDepartment->getDepartmentName() << endl;
        cout << "Start Time: " << employee->getSchedule()->getStartTime() << endl;
        cout << "End Time: " << employee->getSchedule()->getEndTime() << endl;
    } else {
        cout << "Employee not found!" << endl;
    }
}

void searchEmployeeByScheduleID() {
    cout << "Enter the schedule ID (1/2/3): ";
    int scheduleID;
    cin >> scheduleID;
    cin.ignore();
    cout << endl;

    auto range = employeesBySchedule.equal_range(scheduleID);
    if (range.first == range.second) {
        cout << "No employees found with this schedule ID." << endl;
        return;
    }

    for (auto it = range.first; it != range.second; ++it) {
        Employee *employee = it->second;
        cout << "Employee ID: " << employee->getEmployeeID() << endl;
        cout << "Employee Name: " << employee->getEmployeeName() << endl;
        cout << "Date of Birth: " << employee->getDateOfBirth() << endl;
        cout << "Salary: " << employee->getSalary() << endl;
        cout << "Start Time: " << employee->getSchedule()->getStartTime() << endl;
        cout << "End Time: " << employee->getSchedule()->getEndTime() << endl;
        cout << "Department ID: " << employee->getDepartment()->getDepartmentID() << endl;
        cout << "Department Name: " << employee->getDepartment()->getDepartmentName() << endl;
        cout << "Location: " << employee->getDepartment()->getLocation() << endl;
    }
}

void updateMenu(vector<Department *> &departments) {
    int choice;
    do {
        cout << "1.Update employee by ID." << endl;
        cout << "2.Update employee department." << endl;
        cout << "3.Update employee schedule." << endl;
        cout << "4.Back to main menu." << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                system("cls");
                updateEmployeeByID(departments);
                getch();
                system("cls");
                break;
            case 2:
                system("cls");
                updateEmployeeDepartment(departments);
                getch();
                system("cls");
                break;
            case 3:
                system("cls");
                updateEmployeeSchedule(departments);
                getch();
                system("cls");
                break;
            case 4:
                system("cls");
                break;
            default:
                cout << "Invalid choice. Please try again..." << endl;
                getch();
                system("cls");
        }
    } while (choice != 4);
}

void searchMenu(vector<Department *> &departments) {
    int choice;
    do {
        cout << "1.Search employee by ID." << endl;
        cout << "2.Search employee by schedule ID." << endl;
        cout << "3.Back to main menu." << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                system("cls");
                searchEmployeeByID(departments);
                getch();
                system("cls");
                break;
            case 2:
                system("cls");
                searchEmployeeByScheduleID();
                getch();
                system("cls");
                break;
            case 3:
                system("cls");
                break;
            default:
                cout << "Invalid choice. Please try again..." << endl;
                getch();
                system("cls");
        }
    } while (choice != 3);
}

bool mainMenu(vector<Department *> &departments) {
    int choice;
    cout << "1. Create employee." << endl;
    cout << "2. Display departments." << endl;
    cout << "3. Update employee information." << endl;
    cout << "4. Delete employee from department." << endl;
    cout << "5. Search employee." << endl;
    cout << "6. Exit." << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    switch (choice) {
        case 1:
            system("cls");
            createEmployeeMenu(*departments[0], *departments[1], *departments[2]);
            break;
        case 2:
            system("cls");
            displayDepartmentsMenu(*departments[0], *departments[1], *departments[2]);
            break;
        case 3:
            system("cls");
            updateMenu(departments);
            break;
        case 4:
            system("cls");
            deleteEmployeeFromDepartment(departments);
            break;
        case 5:
            system("cls");
            searchMenu(departments);
            break;
        case 6:
            cout << "Exiting program." << endl;
            return false;
        default:
            cout << "Invalid choice. Please try again..." << endl;
            getch();
            system("cls");
    }
    return true;
}

void saveDataToFile(vector<Department *> &departments) {
    ofstream outFile("data.txt");
    if (outFile.is_open()) {
        outFile << usedEmployeeIDs.size() << endl;
        for (const auto &id: usedEmployeeIDs) {
            outFile << id << endl;
        }
        for (const auto &department: departments) {
            for (const auto &employee: department->getEmployees()) {
                outFile << employee->getEmployeeID() << endl;
                outFile << employee->getEmployeeName() << endl;
                outFile << employee->getDateOfBirth() << endl;
                outFile << employee->getSalary() << endl;
                outFile << employee->getSchedule()->getScheduleID() << endl;
                outFile << department->getDepartmentID() << endl;
            }
        }
        outFile.close();
    }
}

void loadDataFromFile(vector<Department *> &departments) {
    ifstream inFile("data.txt");
    if (inFile.is_open()) {
        string line;
        getline(inFile, line);
        int usedEmployeeIDsSize = stoi(line);
        for (int i = 0; i < usedEmployeeIDsSize; i++) {
            getline(inFile, line);
            usedEmployeeIDs.insert(stoi(line));
        }
        while (getline(inFile, line)) {
            string employeeID = line;
            getline(inFile, line);
            string employeeName = line;
            getline(inFile, line);
            string dateOfBirth = line;
            getline(inFile, line);
            double salary = stod(line);
            getline(inFile, line);
            int scheduleID = stoi(line);
            getline(inFile, line);
            string departmentID = line;

            auto *employee = new Employee(employeeID, employeeName, dateOfBirth, salary);
            employee->setSchedule(schedules[scheduleID]);
            for (auto department: departments) {
                if (department->getDepartmentID() == departmentID) {
                    department->addEmployee(employee);
                    break;
                }
            }
            employeesBySchedule.insert(make_pair(scheduleID, employee));
        }
        inFile.close();
    }
}

int main() {
    Department Sales("D001", "Sales", "Hanoi");
    Department Technology("D002", "Technology", "Hanoi");
    Department Finance("D003", "Finance", "Hanoi");
    createSchedules(); //create schedules with ID 1, 2, 3 and start time, end time
    vector<Department *> departments = {&Sales, &Technology, &Finance};
    loadDataFromFile(departments);
    bool running = true;
    while (running) {
        running = mainMenu(departments);
    }
    saveDataToFile(departments);
    return 0;
}