# Employee Management System

This is a C++ program that allows you to manage employees, their schedules, and departments in an organization. The program provides various functionalities to create, display, update, delete, and search for employees.

## Features

- Create employees with unique IDs, names, dates of birth, salaries, and schedules
- Assign employees to different departments (Sales, Technology, Finance)
- Update employee information such as name, date of birth, salary, schedule, and department
- Delete employees from a specific department
- Search employees by their ID or schedule ID
- Display information about departments and their employees
- Save and load employee data from a file

## How to Use

1. Compile and run the program.
2. The program will display a main menu with the following options:
  - Create Employee
  - Display Departments
  - Update Employee Information
  - Delete Employee from Department
  - Search Employee
  - Exit
3. Follow the on-screen instructions to navigate through the different options and perform the desired operations.

## File Structure

- `main.cpp`: Contains the main program logic and implementation of all classes and functions.
- `data.txt`: File used to store and load employee data.

## Dependencies

The program uses the following C++ standard libraries:

- `iostream`: For input/output operations
- `string`: For string manipulation
- `vector`: For dynamic array implementation
- `map`: For associative container implementation
- `fstream`: For file input/output operations
- `set`: For set container implementation
- `conio.h`: For console input/output operations (may need to be replaced on non-Windows systems)

## Contributing

Contributions to this project are welcome. If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).
