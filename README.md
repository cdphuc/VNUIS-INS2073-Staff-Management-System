Employee Management System
Overview
A C++ console application for managing employees, departments, and schedules with file persistence.

Features
Add, update, delete, and search for employees
Assign schedules and manage departmental information
Save and load data to/from a file
Classes
Schedule
Attributes: scheduleID, startTime, endTime
Methods: Constructors, getters, setters
Employee
Attributes: employeeID, employeeName, dateOfBirth, salary, schedule, department
Methods: Constructors, getters, setters, inputEmployee(), displayEmployeeDetails()
Department
Attributes: departmentID, departmentName, location, employees
Methods: Constructors, getters, setters, addEmployee(), deleteEmployee(), displayDepartmentDetails()
Key Functions
createSchedules(): Create predefined schedules.
createEmployeeMenu(): Add new employees.
displayDepartmentsMenu(): Display employees by department.
findEmployeeByID(): Find an employee by ID.
updateEmployeeByID(): Update employee details.
deleteEmployeeFromDepartment(): Delete an employee by ID.
searchEmployeeByID(): Search for an employee by ID.
saveDataToFile(): Save data to data.txt.
loadDataFromFile(): Load data from data.txt.
How to Run
Compile:

Sao chép mã
g++ -o EmployeeManagementSystem EmployeeManagementSystem.cpp
Run:

Sao chép mã
./EmployeeManagementSystem
Follow the on-screen instructions.

Data File (data.txt) Format
php
Sao chép mã
<number_of_used_employee_ids>
<used_employee_id_1>
<used_employee_id_2>
...
<employee_id>
<employee_name>
<date_of_birth>
<salary>
<schedule_id>
<department_id>
...
Place data.txt in the same directory as the executable when running the program.
