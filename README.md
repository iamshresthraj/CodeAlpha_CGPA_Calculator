# CGPA Calculator (C++)

A robust and user-friendly console-based CGPA Calculator written in C++. It allows students to calculate their Semester Grade Point Average (GPA) and Cumulative Grade Point Average (CGPA) over multiple semesters.

## Features
- **Multi-Semester Calculations**: Add and compute statistics across multiple semesters sequentially.
- **Flexible Grade Inputs**: Accepts standard letter grades (A+, A, A-, B+, B, B-, C+, C, C-, D+, D, F) or direct numeric GPA point values (0.0 to 4.0).
- **Validation & Safe Inputs**: Automatically handles invalid credits (must be between 0.5 and 10) and invalid grades, prompting the user to re-enter details instead of crashing.
- **Polished Presentation**: Formats courses, credit hours, and grades in a clean tabular view directly in the console.

## How to Build and Run

### Prerequisites
You need a C++ compiler supporting C++17 or higher (such as GCC/MinGW or Clang).

### Compilation
Open your terminal/command prompt, navigate to the project directory, and compile the code:
```bash
g++ -O3 -Wall -std=c++17 main.cpp -o cgpa_calculator.exe
```

### Execution
Run the compiled executable:
```bash
.\cgpa_calculator.exe
```

## Sample Output
```text
=========================================================
                   ACADEMIC REPORT CARD                  
=========================================================

+-------------------------------------------------------+
| Semester 1                                            |
+----------------------------------+---------+----------+
| Course Name                      | Grade   | Credits  |
+----------------------------------+---------+----------+
| Math                             | A (4.0) |     3.00 |
| English                          | B (3.0) |     3.00 |
+----------------------------------+---------+----------+
| Semester Credits: 6.00           | GPA: 3.50          |
+----------------------------------+--------------------+

=========================================================
                    SUMMARY OVERVIEW                     
=========================================================
 Total Semesters:           1
 Total Credits Earned:      6.00
 Cumulative Grade Points:   21.00
---------------------------------------------------------
 FINAL CGPA: 3.50 / 4.00
=========================================================
```
