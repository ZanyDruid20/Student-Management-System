# Student-Management-System
# Overview
The Student Management System is a software application developed using C++ that utilizes an AVL tree data structure to manage student records efficiently. The AVL tree provides self-balancing properties, ensuring that all basic operations (insertion, deletion, and searching) are performed in logarithmic time complexity. This project serves as an excellent example of using tree structures to maintain ordered data.

# Features
Add Student Record: Allows the addition of a new student record, including name, student ID, department, and GPA.
Remove Student Record: Enables the removal of a student record by their student ID.
Search for Student: Provides functionality to search for a student by their ID and retrieve detailed information (name, ID, department, and GPA).
Display All Students: Displays all student records stored in the system.
Calculate Average GPA: Computes the average GPA of all students in the system.
Update GPA: Updates the GPA of a specific student.

# Code Implementation/Data Structure
The system is built around the TreeNode structure, which represents each student as a node in the AVL tree. Each node contains the following attributes:
name: The student's name.
studentID: A unique identifier for the student.
department: The student's department.
GPA: The student's Grade Point Average.
left and right: Pointers to the left and right child nodes, respectively.
height: The height of the node used for AVL balancing.

# AVL Tree Operations
The StudentInformationSystem class contains methods for inserting, removing, and searching for nodes within the AVL tree. It also includes balancing methods to maintain the AVL property during insertions and deletions.

# Performance Measurement
To evaluate the performance of various operations, the <chrono> library is used. This allows for precise timing of the following functionalities:

Adding student records
Searching for a student by ID
Removing a student record
Updating a student's GPA
Each operation's duration is printed in microseconds to give insight into the efficiency of the implementation.

# Example Usage
Here's a snippet of how the system is used:

int main() {
    StudentInformationSystem system;

    // Adding students
    system.addStudent("Alice", 101, "CS", 3.8);
    system.addStudent("Bob", 102, "Math", 3.5);
    // ... more students

    // Searching for a student
    cout << system.searchStudent(102) << endl;

    // Updating GPA
    system.updateGPA(102, 3.9);

    // Displaying all students
    system.displayAllStudents();

    return 0;
}
# Dependecies
C++ Standard Library
<chrono> library for performance measurement
# Conclusion
This project demonstrates the application of AVL trees in managing student records effectively. The system is designed to be efficient and scalable, making it suitable for larger datasets.

