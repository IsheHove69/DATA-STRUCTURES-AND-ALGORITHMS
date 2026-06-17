# Student Grade Checker – Group 7

## Overview

The **Student Grade Checker** is a C++17 console-based application designed to manage student academic records. It allows users to enroll students, record marks for multiple subjects across several terms, calculate grades and GPA automatically, view detailed student performance, and generate class statistics.

The project demonstrates the practical use of **Data Structures and Algorithms (DSA)** concepts such as **queues**, **vectors**, **sorting algorithms**, and **search operations**.

---

## Features

### Student Management

* Add new students
* Remove existing students
* Automatically assign unique student IDs
* Prevent duplicate student names

### Academic Records

* Record marks for multiple subjects
* Support up to:

  * **10 subjects per term**
  * **5 terms per student**
* Automatically calculate:

  * Average score
  * Letter grade
  * GPA

### Display Options

* View complete student details
* Display students:

  * Alphabetically (A–Z)
  * By grade ascending
  * By grade descending
  * By enrollment order (FIFO)

### Statistics

* Total number of students
* Number of students with recorded grades
* Class average
* Highest-performing student
* Lowest-performing student

---

## Data Structures Used

### Queue (`queue<Student>`)

Used as the primary storage structure.

**Purpose:**

* Maintains student enrollment order
* Follows **FIFO (First In, First Out)** principles
* New students are added to the back of the queue

### Vector (`vector<Student>`)

Used for:

* Sorting student records
* Displaying information
* Modifying student data

### Additional STL Components

* `algorithm`

  * `sort()`
  * `find_if()`
* `numeric`

  * `accumulate()`
* `string`
* `iomanip`

---

## Grade Scale

| Average (%) | Grade | GPA |
| ----------- | ----- | --- |
| 90 – 100    | A+    | 4.0 |
| 85 – 89     | A     | 4.0 |
| 80 – 84     | A-    | 3.7 |
| 75 – 79     | B+    | 3.3 |
| 70 – 74     | B     | 3.0 |
| 65 – 69     | B-    | 2.7 |
| 60 – 64     | C+    | 2.3 |
| 55 – 59     | C     | 2.0 |
| 50 – 54     | C-    | 1.7 |
| 45 – 49     | D     | 1.0 |
| Below 45    | F     | 0.0 |

---

## Menu Options

```text
[1] Add student
[2] Remove student
[3] Enter marks (new term)
[4] View student detail
[5] Display all → Alphabetical (A-Z)
[6] Display all → Grade ascending
[7] Display all → Grade descending
[8] Display all → Enrollment order (queue)
[9] Class statistics
[0] Exit
```

---

## Compilation

### Using g++

```bash
g++ -std=c++17 algo.cpp -o grade_checker
```

### Run

```bash
./grade_checker
```

---

## Example Workflow

### Add a Student

```text
Enter student name: John Doe
[✓] Added "John Doe" (ID 001)
```

### Enter Marks

```text
Number of subjects: 3

Mathematics: 85
Physics: 90
Programming: 88
```

### Output

```text
Term 1 saved.
Avg: 87.67
Grade: A
GPA: 4.0
```

---

## Algorithm Complexity

| Operation        | Time Complexity |
| ---------------- | --------------- |
| Add Student      | O(1)            |
| Remove Student   | O(n)            |
| Search Student   | O(n)            |
| Enter Marks      | O(n)            |
| Sort Students    | O(n log n)      |
| Display Students | O(n)            |
| Class Statistics | O(n)            |

---

## Input Validation

The program validates:

* Empty names
* Duplicate student names
* Subject count limits
* Term count limits
* Marks between 0 and 100
* Invalid menu selections

---

## Learning Objectives

This project demonstrates:

* Queue data structure (FIFO)
* Dynamic arrays using vectors
* Sorting algorithms
* Searching algorithms
* GPA and grade calculations
* Structured programming in C++
* User input validation
* Academic record management systems

---

## Authors

**Group 7**

Student Grade Checker Project
Language: **C++**
Course: **Data Structures and Algorithms (DSA)**

---

## Future Improvements

* File storage (save/load student records)
* Student search by ID
* Subject performance analytics
* Graphical User Interface (GUI)
* Database integration
* Export reports to PDF/CSV
* Authentication system for administrators
* Semester comparison charts

---

