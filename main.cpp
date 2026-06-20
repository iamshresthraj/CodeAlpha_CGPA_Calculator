#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <limits>
#include <sstream>

// Structures for organizing data
struct Course {
    std::string name;
    std::string gradeInput;
    double gradePoints;
    double creditHours;
};

struct Semester {
    int semesterNumber;
    std::vector<Course> courses;
    double totalCredits;
    double totalGradePoints;
    double semesterGPA;
};

// Helper function to trim whitespaces from a string
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

// Convert letter grade to grade points or parse numeric grade points
double parseGrade(std::string gradeInput, bool& isValid) {
    gradeInput = trim(gradeInput);
    // Convert to uppercase for comparison
    std::transform(gradeInput.begin(), gradeInput.end(), gradeInput.begin(), ::toupper);

    if (gradeInput.empty()) {
        isValid = false;
        return 0.0;
    }

    isValid = true;

    // Standard 4.0 grading scale mapping
    if (gradeInput == "A+" || gradeInput == "A") return 4.0;
    if (gradeInput == "A-") return 3.7;
    if (gradeInput == "B+") return 3.3;
    if (gradeInput == "B") return 3.0;
    if (gradeInput == "B-") return 2.7;
    if (gradeInput == "C+") return 2.3;
    if (gradeInput == "C") return 2.0;
    if (gradeInput == "C-") return 1.7;
    if (gradeInput == "D+") return 1.3;
    if (gradeInput == "D") return 1.0;
    if (gradeInput == "F") return 0.0;

    // Try parsing as double directly (in case user inputs grade points directly, e.g., 3.65)
    try {
        size_t idx;
        double val = std::stod(gradeInput, &idx);
        if (idx == gradeInput.length() && val >= 0.0 && val <= 4.0) {
            return val;
        }
    } catch (...) {
        // Parsing failed or value out of bounds
    }

    isValid = false;
    return 0.0;
}

// Safe numeric double input
double getDoubleInput(const std::string& prompt, double minVal, double maxVal) {
    double value;
    std::string input;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, input)) {
            std::cout << "Input read error. Please try again.\n";
            continue;
        }
        input = trim(input);
        try {
            size_t idx;
            value = std::stod(input, &idx);
            if (idx == input.length() && value >= minVal && value <= maxVal) {
                return value;
            }
        } catch (...) {}
        std::cout << "Invalid input. Please enter a numerical value between " << minVal << " and " << maxVal << ".\n";
    }
}

// Safe numeric integer input
int getIntInput(const std::string& prompt, int minVal, int maxVal) {
    int value;
    std::string input;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, input)) {
            std::cout << "Input read error. Please try again.\n";
            continue;
        }
        input = trim(input);
        try {
            size_t idx;
            value = std::stoi(input, &idx);
            if (idx == input.length() && value >= minVal && value <= maxVal) {
                return value;
            }
        } catch (...) {}
        std::cout << "Invalid input. Please enter an integer between " << minVal << " and " << maxVal << ".\n";
    }
}

// Safe grade input containing either letter or numeric grade point
Course getCourseInput(int courseIndex) {
    Course c;
    std::cout << "\n--- Course " << courseIndex << " ---\n";
    
    // Read course name
    std::cout << "Enter Course Name (or press Enter to use default 'Course " << courseIndex << "'): ";
    std::getline(std::cin, c.name);
    c.name = trim(c.name);
    if (c.name.empty()) {
        c.name = "Course " + std::to_string(courseIndex);
    }

    // Read credit hours
    c.creditHours = getDoubleInput("Enter Credit Hours (0.5 to 10.0): ", 0.5, 10.0);

    // Read grade
    bool isValidGrade = false;
    while (!isValidGrade) {
        std::cout << "Enter Grade (Letter: A+, A, A-, B+, etc. OR Grade Point: 0.0 - 4.0): ";
        std::getline(std::cin, c.gradeInput);
        c.gradePoints = parseGrade(c.gradeInput, isValidGrade);
        if (!isValidGrade) {
            std::cout << "Invalid grade format. Please enter a valid letter grade (A/B/C/D/F with optional +/-) or a point value between 0.0 and 4.0.\n";
        }
    }

    return c;
}

int main() {
    // Beautiful Header
    std::cout << "=========================================================\n";
    std::cout << "                   CGPA CALCULATOR                       \n";
    std::cout << "=========================================================\n";

    int totalSemesters = getIntInput("Enter the number of semesters: ", 1, 20);
    std::vector<Semester> semesters;

    double cumulativeGradePoints = 0.0;
    double cumulativeCredits = 0.0;

    for (int s = 1; s <= totalSemesters; ++s) {
        std::cout << "\n=========================================================\n";
        std::cout << "                     SEMESTER " << s << "                     \n";
        std::cout << "=========================================================\n";

        int numCourses = getIntInput("Enter the number of courses for this semester: ", 1, 15);
        Semester currentSemester;
        currentSemester.semesterNumber = s;
        currentSemester.totalCredits = 0.0;
        currentSemester.totalGradePoints = 0.0;

        for (int c = 1; c <= numCourses; ++c) {
            Course course = getCourseInput(c);
            currentSemester.courses.push_back(course);
            currentSemester.totalCredits += course.creditHours;
            currentSemester.totalGradePoints += (course.gradePoints * course.creditHours);
        }

        if (currentSemester.totalCredits > 0.0) {
            currentSemester.semesterGPA = currentSemester.totalGradePoints / currentSemester.totalCredits;
        } else {
            currentSemester.semesterGPA = 0.0;
        }

        cumulativeCredits += currentSemester.totalCredits;
        cumulativeGradePoints += currentSemester.totalGradePoints;

        semesters.push_back(currentSemester);
    }

    // Output formatted report
    std::cout << "\n\n";
    std::cout << "=========================================================\n";
    std::cout << "                   ACADEMIC REPORT CARD                  \n";
    std::cout << "=========================================================\n";

    for (const auto& sem : semesters) {
        std::cout << "\n+-------------------------------------------------------+\n";
        std::cout << "| Semester " << std::left << std::setw(45) << sem.semesterNumber << "|\n";
        std::cout << "+----------------------------------+---------+----------+\n";
        std::cout << "| " << std::left << std::setw(32) << "Course Name" 
                  << "| " << std::left << std::setw(8) << "Grade" 
                  << "| " << std::left << std::setw(8) << "Credits" << "|\n";
        std::cout << "+----------------------------------+---------+----------+\n";

        for (const auto& course : sem.courses) {
            std::string gradeStr = course.gradeInput;
            // Trim and capitalize grade name for output
            std::transform(gradeStr.begin(), gradeStr.end(), gradeStr.begin(), ::toupper);
            gradeStr = trim(gradeStr);
            
            // Format grade output display: letter grades show points in parens, numeric grades show value directly
            std::stringstream ss;
            bool isLetterGrade = false;
            if (!gradeStr.empty() && std::isalpha(static_cast<unsigned char>(gradeStr[0]))) {
                isLetterGrade = true;
            }

            if (isLetterGrade) {
                ss << gradeStr << " (" << std::fixed << std::setprecision(1) << course.gradePoints << ")";
            } else {
                ss << std::fixed << std::setprecision(2) << course.gradePoints;
            }
            
            std::cout << "| " << std::left << std::setw(32) << (course.name.length() > 32 ? course.name.substr(0, 29) + "..." : course.name)
                      << "| " << std::left << std::setw(8) << ss.str()
                      << "| " << std::right << std::setw(8) << std::fixed << std::setprecision(2) << course.creditHours << " |\n";
        }
        std::cout << "+----------------------------------+---------+----------+\n";
        std::cout << "| Semester Credits: " << std::left << std::setw(14) << std::fixed << std::setprecision(2) << sem.totalCredits
                  << " | GPA: " << std::left << std::setw(15) << std::fixed << std::setprecision(2) << sem.semesterGPA << "|\n";
        std::cout << "+----------------------------------+--------------------+\n";
    }

    double finalCGPA = 0.0;
    if (cumulativeCredits > 0.0) {
        finalCGPA = cumulativeGradePoints / cumulativeCredits;
    }

    std::cout << "\n=========================================================\n";
    std::cout << "                    SUMMARY OVERVIEW                     \n";
    std::cout << "=========================================================\n";
    std::cout << std::left << std::setw(28) << " Total Semesters:" << totalSemesters << "\n";
    std::cout << std::left << std::setw(28) << " Total Credits Earned:" << std::fixed << std::setprecision(2) << cumulativeCredits << "\n";
    std::cout << std::left << std::setw(28) << " Cumulative Grade Points:" << std::fixed << std::setprecision(2) << cumulativeGradePoints << "\n";
    std::cout << "---------------------------------------------------------\n";
    std::cout << " FINAL CGPA: " << std::fixed << std::setprecision(2) << finalCGPA << " / 4.00\n";
    std::cout << "=========================================================\n";

    std::cout << "\nPress Enter to exit...";
    std::string exitWait;
    std::getline(std::cin, exitWait);

    return 0;
}
