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
    Schedule(int scheduleID, string startTime, string endTime) { //Schedule constructor
        this->scheduleID = scheduleID;
        this->startTime = startTime;
        this->endTime = endTime;
    }

    int getScheduleID() const { //get schedule ID
        return scheduleID;
    }

    string getStartTime() const { //get start time
        return startTime;
    }

    string getEndTime() const { //get end time
        return endTime;
    }
};

class Department; //forward declaration

set<int> usedEmployeeIDs; //set to store used employee IDs

class Employee {
private:
    string employeeID, employeeName, dateOfBirth;
    double salary;
    Schedule* schedule; //Employee schedule
    Department* department; //Employee department
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

    void setSalary(const double& salary) { //set employee salary
        this->salary = salary;
    }

    Schedule* getSchedule() const { //get employee schedule
        return schedule;
    }

    void setEmployeeName(const string& employeeName) { //set employee name
        this->employeeName = employeeName;
    }

    void setDateOfBirth(const string& dateOfBirth) { //set employee birthday
        this->dateOfBirth = dateOfBirth;
    }

    void setSchedule(Schedule* schedule) { //set employee schedule
        this->schedule = schedule;
    }

    void setDepartment(Department* department) { //set employee department
        this->department = department;
    }

    Department* getDepartment() const { //get employee department
        return department;
    }

    void inputEmployee() { //enter employee from keyboard
        int newEmployeeID = 1;
        while (usedEmployeeIDs.find(newEmployeeID) != usedEmployeeIDs.end()) { //check if the employee ID is already used
            newEmployeeID++;
        }
        usedEmployeeIDs.insert(newEmployeeID);
        this->employeeID = "E" + string(3 - to_string(newEmployeeID).length(), '0') + to_string(newEmployeeID); //auto  generate employee ID
        cout << "Enter employee name: ";
        getline(cin, this->employeeName);
        cout << "Enter date of birth (YYYY/MM/DD): ";
        cin >> this->dateOfBirth;
        cout << "Enter salary: ";
        cin >> this->salary;
        cin.ignore();
    }

    void displayEmployeeDetails() const { //display employee details
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

class Department { //Department class
private:
    string departmentID, departmentName, location;
    vector<Employee*> employees; //vector to store employees in the department
public:
    Department() = default; //Department default constructor
    Department(string departmentID, string departmentName, string location) {
        this->departmentID = departmentID;
        this->departmentName = departmentName;
        this->location = location;
    }

    string getDepartmentID() const { //get department ID
        return departmentID;
    }

    string getDepartmentName() const { //get department name
        return departmentName;
    }

    string getLocation() const { //get department location
        return location;
    }

    vector<Employee*> getEmployees() const { //get employees in the department
        return employees;
    }

    void addEmployee(Employee* employee) { //add employee to the department
        employees.push_back(employee); //add the employee to the employees vector
        employee->setDepartment(this); //set the employee department
    }

    void deleteEmployee(const string& employeeID) { //delete employee from the department
        for (auto it = employees.begin(); it != employees.end(); ++it) { //loop through the employees vector
            if ((*it)->getEmployeeID() == employeeID) { //check if the employee ID is the same
                employees.erase(it); //erase the employee from the vector
                break;
            }
        }
    }

    void displayDepartmentDetails() { //display department details
        cout << "Department ID: " << departmentID << endl;
        cout << "Department Name: " << departmentName << endl;
        cout << "Location: " << location << endl << endl;
        cout << "Employees: " << endl;
        for (auto& employee : employees) {
            employee->displayEmployeeDetails();
            cout << endl;
        }
    }
};

map<int, Schedule*> schedules; //map to store schedules
multimap<int, Employee*> employeesBySchedule; //multimap to store employees by schedule ID

void createSchedules() { //create schedules
    schedules[1] = new Schedule(1, "08:00", "16:00");
    schedules[2] = new Schedule(2, "09:00", "17:00");
    schedules[3] = new Schedule(3, "10:00", "18:00");
}

void createEmployeeMenu(Department& Sales, Department& Technology, Department& Finance) { //create employee menu
    int numEmployees, successCreation;
    cout << "Enter the number of employee(s): ";
    cin >> numEmployees;
    cin.ignore();
    successCreation = numEmployees; //number of successfully created employees
    for (int i = 0; i < numEmployees; i++) { //loop to create employees
        cout << endl;
        cout << "Enter details for employee " << i + 1 << endl;
        auto* emp = new Employee(); //create new employee object
        emp->inputEmployee(); //enter employee details
        //set employee schedule
        int scheduleID;
        cout << "Available schedules: " << endl;
        for (auto& schedule : schedules) {
            cout << "Schedule ID: " << schedule.first << " Start Time: " << schedule.second->getStartTime()
                 << " End Time: " << schedule.second->getEndTime() << endl;
        }
        cout << "Enter schedule ID: ";
        cin >> scheduleID;
        cin.ignore();
        if (schedules.find(scheduleID) != schedules.end()) { //check if the schedule ID is valid
            emp->setSchedule(schedules[scheduleID]); //set employee schedule
            employeesBySchedule.insert(make_pair(scheduleID, emp)); //add the new entry to the employeesBySchedule map
        }
        else {
            cout << "Employee creation failed. Invalid schedule ID." << endl;
            delete emp; //delete the employee object if the schedule ID is invalid
            successCreation--; //decrement the number of successfully created employees
            continue; //skip the rest of the loop
        }
        //add employee to the department
        string departmentChoice;
        cout << "Enter the department (Sales/Technology/Finance): ";
        getline(cin, departmentChoice);
        if (departmentChoice == "Sales") { //check if the department is Sales
            Sales.addEmployee(emp);
            cout << "Employee created successfully." << endl;
        }
        else if (departmentChoice == "Technology") { //check if the department is Technology
            Technology.addEmployee(emp);
            cout << "Employee created successfully." << endl;
        }
        else if (departmentChoice == "Finance") { //check if the department is Finance
            Finance.addEmployee(emp);
            cout << "Employee created successfully." << endl;
        }
        else { //if the department is not available
            cout << "Employee creation failed. No department available." << endl;
            delete emp; //delete the employee object
            successCreation--; //decrement the number of successfully created employees
        }
    }
    cout << "Successfully created " << successCreation << "/" << numEmployees << " employee(s)." << endl; //display the number of successfully created employees
    (void)_getch();
    system("cls");
}

void displayDepartmentsMenu(Department& Sales, Department& Technology, Department& Finance) { //display departments menu
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
            case 1: //display sales department if choice is 1
                system("cls");
                Sales.displayDepartmentDetails();
                (void)_getch();
                system("cls");
                break;
            case 2: //display technology department if choice is 2
                system("cls");
                Technology.displayDepartmentDetails();
                (void)_getch();
                system("cls");
                break;
            case 3: //display finance department if choice is 3
                system("cls");
                Finance.displayDepartmentDetails();
                (void)_getch();
                system("cls");
                break;
            case 4: //display all departments if choice is 4
                system("cls");
                Sales.displayDepartmentDetails();
                cout << endl;
                Technology.displayDepartmentDetails();
                cout << endl;
                Finance.displayDepartmentDetails();
                (void)_getch();
                system("cls");
                break;
            case 5: //back to main menu if choice is 5
                system("cls");
                break;
            default: //invalid choice
                cout << "Invalid choice. Please try again..." << endl;
                (void)_getch();
                system("cls");
        }
    } while (choice != 5); //loop until choice is 5
}


Department* findDepartmentByName(const string& departmentName, vector<Department*>& departments) { //find department by name
    for (auto department : departments) {
        if (department->getDepartmentName() == departmentName) { //check if the department name is the same
            return department; //return the department if found
        }
    }
    return nullptr; //return null if the department is not found
}

Employee* findEmployeeByID(const string& employeeID, Department* department) { //find employee by ID
    for (auto employee : department->getEmployees()) { //loop through the employees in the department
        if (employee->getEmployeeID() == employeeID) { //check if the employee ID is the same
            return employee; //return the employee if found
        }
    }
    return nullptr; //return null if the employee is not found
}

void updateEmployeeByID(vector<Department*>& departments) { //update employee by ID
    cout << "Enter the department that needs to update employee information (Sales/Technology/Finance): ";
    string departmentName;
    getline(cin, departmentName);

    Department* department = findDepartmentByName(departmentName, departments); //find department by name
    if (!department) { //check if the department is not found
        cout << "Department not found!" << endl;
        return; //return if the department is not found
    }
    else {
        if (department->getEmployees().empty()) { //check if the department has no employees
            cout << "No employees found in this department." << endl;
            return; //return if the department has no employees
        }
        else {
            department->displayDepartmentDetails(); //display department details if the department has employees
        }
    }
    //update employee information
    cout << "Enter the employee ID to update: ";
    string employeeID;
    cin >> employeeID;
    cin.ignore();

    Employee* employee = findEmployeeByID(employeeID, department); //find employee by ID
    if (employee) { //check if the employee is found
        cout << "Enter new employee name: ";
        string newEmployeeName; //enter new employee name
        getline(cin, newEmployeeName);
        employee->setEmployeeName(newEmployeeName); //update employee name

        cout << "Enter new date of birth: ";
        string newDateOfBirth; //enter new date of birth
        cin >> newDateOfBirth;
        employee->setDateOfBirth(newDateOfBirth); //update date of birth

        cout << "Enter new salary: ";
        double newSalary; //enter new salary
        cin >> newSalary;
        employee->setSalary(newSalary); //update salary
        cin.ignore();

        cout << "Employee updated successfully." << endl;
    }
}

void updateEmployeeSchedule(vector<Department*>& departments) { //update employee schedule
    cout << "Enter the department that needs to update employee schedule (Sales/Technology/Finance): ";
    string departmentName;
    getline(cin, departmentName);
    Department* department = findDepartmentByName(departmentName, departments); //find department by name
    if (!department) { //check if the department is not found
        cout << "Department not found!" << endl;
        return; //return if the department is not found
    }
    else {
        if (department->getEmployees().empty()) { //check if the department has no employees
            cout << "No employees found in this department." << endl;
            return; //return if the department has no employees
        }
        else {
            department->displayDepartmentDetails(); //display department details if the department has employees
        }
    }
    cout << "Enter the employee ID to update schedule: ";
    string employeeID;
    cin >> employeeID;
    cin.ignore();
    Employee* employee = findEmployeeByID(employeeID, department); //find employee by ID
    if (employee) { //check if the employee is found
        int newScheduleID;
        cout << "Available schedules: " << endl; //display available schedules
        for (auto& schedule : schedules) {
            cout << "Schedule ID: " << schedule.first << " Start Time: " << schedule.second->getStartTime()
                 << " End Time: " << schedule.second->getEndTime() << endl;
        }
        bool validScheduleID = false; //flag to check if the schedule ID is valid
        while (!validScheduleID) { //loop until the schedule ID is valid
            cout << "Enter new schedule ID: "; //enter new schedule ID 1 or 2 or 3
            cin >> newScheduleID;
            cin.ignore();
            if (schedules.find(newScheduleID) != schedules.end()) { //check if the schedule ID is valid
                for (auto it = employeesBySchedule.begin(); it != employeesBySchedule.end(); ++it) { //loop through the employeesBySchedule map
                    if (it->second == employee) { //check if the employee is found
                        employeesBySchedule.erase(it); //erase the employee from the map
                        break; //break the loop
                    }
                }
                employee->setSchedule(schedules[newScheduleID]); //Update employee schedule with the new schedule ID
                employeesBySchedule.insert(make_pair(newScheduleID, employee)); //Add the new entry to the employeesBySchedule map
                cout << "Employee updated successfully." << endl;
                validScheduleID = true; //set the flag to true and exit the loop
            }
            else { //if the schedule ID is invalid
                cout << "Invalid schedule ID. Please try again." << endl; //display error message and try again
            }
        }
    }
}


void updateEmployeeDepartment(vector<Department*>& departments) { //update employee department
    for (auto department : departments) { //loop through the departments
        department->displayDepartmentDetails(); //display department details
    }
    cout << "Enter the employee ID to change department: ";
    string employeeID;
    cin >> employeeID;
    cin.ignore();

    Department* currentDepartment = nullptr;
    Employee* employee = nullptr;
    for (auto department : departments) { //loop through the departments
        employee = findEmployeeByID(employeeID, department); //find employee by ID
        if (employee) { //check if the employee is found
            currentDepartment = department; //set the current department to the department where the employee is found
            break; //break the loop
        }
    }

    if (!employee) { //check if the employee is not found
        cout << "Employee not found." << endl; //display error message
        return; //return if the employee is not found
    }

    cout << "Enter the new department name (Sale/Technology/Finance): "; //enter the new department name
    string newDepartmentName;
    getline(cin, newDepartmentName);

    Department* newDepartment = findDepartmentByName(newDepartmentName, departments); //find the new department by name
    if (!newDepartment) { //check if the new department is not found
        cout << "Department not found." << endl;
        return; //return if the new department is not found
    }

    currentDepartment->deleteEmployee(employeeID); //delete the employee from the current department
    newDepartment->addEmployee(employee); //add the employee to the new department
    cout << "Employee department changed successfully." << endl;
}

void deleteEmployeeFromDepartment(vector<Department*>& departments) { //delete employee from department
    cout << "Enter the name of the department that employee to be deleted (Sales/Technology/Finance): ";
    string departmentName;
    getline(cin, departmentName);
    Department* department = findDepartmentByName(departmentName, departments); //find department by name
    if (!department) { //check if the department is not found
        cout << "Department not found." << endl;
        return;
    }
    else {
        if (department->getEmployees().empty()) { //check if the department has no employees
            cout << "No employees found in this department." << endl;
            return;
        }
        else {
            department->displayDepartmentDetails(); //display department details if the department has employees
        }
    }
    cout << "Enter the employee ID to delete: ";
    string employeeID;
    cin >> employeeID;
    cin.ignore();
    Employee* employee = findEmployeeByID(employeeID, department); //find employee by ID
    if (employee) {
        department->deleteEmployee(employeeID); //delete the employee from the department
        usedEmployeeIDs.erase(stoi(employee->getEmployeeID().substr(1))); //erase the employee ID from the usedEmployeeIDs set
        cout << "Employee deleted successfully." << endl;
        (void)_getch();
        system("cls");
    }
    else {
        cout << "Employee not found." << endl; //display error message if the employee is not found
        (void)_getch();
        system("cls");
    }
}

void searchEmployeeByID(vector<Department*>& departments) { //search employee by ID
    cout << "Enter the employee ID to search: ";
    string employeeID;
    cin >> employeeID;
    cin.ignore();
    employeeID[0] = toupper(employeeID[0]); //convert the first character to uppercase
    cout << endl;

    Department* employeeDepartment = nullptr; //initialize employee department to null
    Employee* employee = nullptr; //initialize employee to null
    for (auto department : departments) { //loop through the departments
        employee = findEmployeeByID(employeeID, department); //find employee by ID
        if (employee) {
            employeeDepartment = department; //set the employee department to the department where the employee is found
            break;
        }
    }
    if (employee) { //check if the employee is found and display the employee details
        cout << "Employee name: " << employee->getEmployeeName() << endl;
        cout << "Date of birth: " << employee->getDateOfBirth() << endl;
        cout << "Salary: " << employee->getSalary() << endl;
        cout << "Department ID: " << employeeDepartment->getDepartmentID() << endl;
        cout << "Department: " << employeeDepartment->getDepartmentName() << endl;
        cout << "Start Time: " << employee->getSchedule()->getStartTime() << endl;
        cout << "End Time: " << employee->getSchedule()->getEndTime() << endl;
    }
    else { //if the employee is not found
        cout << "Employee not found!" << endl;
    }
}

void searchEmployeeByScheduleID() { //search employee by schedule ID
    cout << "Enter the schedule ID (1/2/3): ";
    int scheduleID;
    cin >> scheduleID;
    cin.ignore();
    cout << endl;

    auto range = employeesBySchedule.equal_range(scheduleID); //get the range of employees with the schedule ID
    if (range.first == range.second) { //check if the range is empty
        cout << "No employees found with this schedule ID." << endl;
        return;
    }

    for (auto it = range.first; it != range.second; ++it) { //loop through the range of employees
        Employee* employee = it->second; //get the employee from the map entry and display the employee details
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

void updateMenu(vector<Department*>& departments) { //update menu
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
                (void)_getch();
                system("cls");
                break;
            case 2:
                system("cls");
                updateEmployeeDepartment(departments);
                (void)_getch();
                system("cls");
                break;
            case 3:
                system("cls");
                updateEmployeeSchedule(departments);
                (void)_getch();
                system("cls");
                break;
            case 4:
                system("cls");
                break;
            default:
                cout << "Invalid choice. Please try again..." << endl;
                (void)_getch();
                system("cls");
        }
    } while (choice != 4);
}

void searchMenu(vector<Department*>& departments) { //search menu
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
                (void)_getch();
                system("cls");
                break;
            case 2:
                system("cls");
                searchEmployeeByScheduleID();
                (void)_getch();
                system("cls");
                break;
            case 3:
                system("cls");
                break;
            default:
                cout << "Invalid choice. Please try again..." << endl;
                (void)_getch();
                system("cls");
        }
    } while (choice != 3);
}

bool mainMenu(vector<Department*>& departments) { //main menu
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
            (void)_getch();
            system("cls");
    }
    return true;
}

void saveDataToFile(vector<Department*>& departments) { //save data to file
    ofstream outFile("data.txt"); //open the file for writing
    if (outFile.is_open()) { //check if the file is open
        outFile << usedEmployeeIDs.size() << endl; //write the size of the usedEmployeeIDs set
        for (const auto& id : usedEmployeeIDs) { //loop through the usedEmployeeIDs set and write the employee IDs to the file
            outFile << id << endl;
        }
        for (const auto& department : departments) { //loop through the departments
            for (const auto& employee : department->getEmployees()) { //loop through the employees in the department
                outFile << employee->getEmployeeID() << endl; //write the employee details to the file
                outFile << employee->getEmployeeName() << endl; //write the employee name to the file
                outFile << employee->getDateOfBirth() << endl; //write the employee date of birth to the file
                outFile << employee->getSalary() << endl; //write the employee salary to the file
                outFile << employee->getSchedule()->getScheduleID() << endl; //write the employee schedule ID to the file
                outFile << department->getDepartmentID() << endl; //write the department ID to the file
            }
        }
        outFile.close(); //close the file
    }
}

void loadDataFromFile(vector<Department*>& departments) { //load data from file
    ifstream inFile("data.txt"); //open the file for reading
    if (inFile.is_open()) { //check if the file is open
        string line; //string to store the line read from the file
        getline(inFile, line); //read the first line from the file
        int usedEmployeeIDsSize = stoi(line); //convert the line to an integer
        for (int i = 0; i < usedEmployeeIDsSize; i++) { //loop to read the employee IDs from the file
            getline(inFile, line); //read the employee ID from the file
            usedEmployeeIDs.insert(stoi(line)); //insert the employee ID to the usedEmployeeIDs set
        }
        while (getline(inFile, line)) { //loop to read the employee details from the file
            string employeeID = line;
            getline(inFile, line);
            string employeeName = line;
            getline(inFile, line);
            string dateOfBirth = line;
            getline(inFile, line);
            double salary = stod(line); //convert the line to a double
            getline(inFile, line);
            int scheduleID = stoi(line); //convert the line to an integer
            getline(inFile, line);
            string departmentID = line;

            auto* employee = new Employee(employeeID, employeeName, dateOfBirth, salary); //create a new employee object
            employee->setSchedule(schedules[scheduleID]); //set the employee schedule
            for (auto department : departments) { //loop through the departments
                if (department->getDepartmentID() == departmentID) { //check if the department ID is the same
                    department->addEmployee(employee); //add the employee to the department
                    break;
                }
            }
            employeesBySchedule.insert(make_pair(scheduleID, employee)); //add the new entry to the employeesBySchedule map
        }
        inFile.close();
    }
}

int main() {
    Department Sales("D001", "Sales", "Hanoi"); //create departments
    Department Technology("D002", "Technology", "Hanoi");
    Department Finance("D003", "Finance", "Hanoi");
    createSchedules(); //create schedules with ID 1, 2, 3 and start time, end time
    vector<Department*> departments = { &Sales, &Technology, &Finance }; //store departments in a vector
    loadDataFromFile(departments); //load data from file when the program starts
    bool running = true; //flag to check if the program is running
    while (running) { //loop until the program is running
        running = mainMenu(departments); //display the main menu
    }
    saveDataToFile(departments); //save data to file when the program exits
    return 0;
}
