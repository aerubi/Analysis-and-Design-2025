// ProjectTwo.cpp
// Advising Assistance Program
// Author: Aero Berry
// Date: 2025-10-18

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::vector;

// This will trim any whitespace from both ends of a string like course numbers.
static inline string trim(const string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) ++start;
    if (start == s.size()) return "";

    size_t end = s.size() - 1;
    while (end > start && std::isspace(static_cast<unsigned char>(s[end]))) --end;
    return s.substr(start, end - start + 1);
}

// This will split the CSV line by commas into tokens for easier use.
static inline vector<string> splitCSVLine(const string& line) {
    vector<string> tokens;
    string token;
    stringstream ss(line);
    while (std::getline(ss, token, ',')) {
        tokens.push_back(trim(token));
    }
    return tokens;
}


struct Course {
	string courseNumber;            // Stores the course number.
	string courseTitle;             // Stores the course title.
    vector<string> prereqNumbers;   // List of the prerequisite course numbers as strings.
};


class CourseManager {
private:
    // Hash map from course number to Course.
    unordered_map<string, Course> courseTable;
    bool dataLoaded = false;

public:
	// Loads course data from our specified CSV file into the hash table.
    bool loadFromFile() {
        string filename = "CS 300 ABCU_Advising_Program_Input.csv";
        std::ifstream infile(filename);
        if (!infile.is_open()) {
            cout << "Error: Unable to open file '" << filename << "'." << endl;
            return false;
        }

        vector<Course> tempCourses;
        string line;
        int lineNumber = 0;

        while (std::getline(infile, line)) {
            lineNumber++;

            // Skips any blank lines.
            if (line.find_first_not_of(" \t\r\n") == string::npos) continue;

            // Split the tokens by commas.
            vector<string> tokens;
            string token;
            stringstream ss(line);
            while (getline(ss, token, ',')) {
                // Remove any whitespace from ends.
                size_t start = token.find_first_not_of(" \t\r\n");
                size_t end = token.find_last_not_of(" \t\r\n");
                if (start != string::npos)
                    tokens.push_back(token.substr(start, end - start + 1));
                else
                    tokens.push_back("");
            }

            // At least a course number and title are required.
            if (tokens.size() < 2) {
                cout << "Warning: Invalid line " << lineNumber << " ignored." << endl;
                continue;
            }

            Course c;
            c.courseNumber = tokens[0];
            c.courseTitle = tokens[1];

            for (size_t i = 2; i < tokens.size(); ++i) {
                if (!tokens[i].empty())
                    c.prereqNumbers.push_back(tokens[i]);
            }

            tempCourses.push_back(c);
        }

        infile.close();

        // Loads it into hash table.
        courseTable.clear();
        for (auto& c : tempCourses) {
            courseTable[c.courseNumber] = c;
        }

        dataLoaded = true;
        cout << "Successfully loaded " << courseTable.size()
            << " courses from " << filename << "." << endl;
        return true;
    }

    // Prints all courses in alphanumeric order (courseNumber: courseTitle).
    void printAllCoursesSorted() const {
        if (!dataLoaded) {
            cout << "No data loaded. Please select Option 1 to load the file first." << endl;
            return;
        }

        // Extract keys (course numbers).
        vector<string> keys;
        keys.reserve(courseTable.size());
        for (const auto& kv : courseTable) keys.push_back(kv.first);

        // Sort the courses alphanumerically.
        std::sort(keys.begin(), keys.end());

        cout << "Alphanumeric list of all courses:" << endl;
        for (const auto& k : keys) {
            const Course& c = courseTable.at(k);
            cout << c.courseNumber << ": " << c.courseTitle << endl;
        }
    }

    // Print course details: title and prerequisites, both numbers and titles.
    void printCourseInfo(const string& courseNumber) const {
        if (!dataLoaded) {
            cout << "No data loaded. Please select Option 1 to load the file first." << endl;
            return;
        }

        auto it = courseTable.find(courseNumber);
        if (it == courseTable.end()) {
            cout << "Course '" << courseNumber << "' not found." << endl;
            return;
        }

        const Course& c = it->second;
        cout << "Course Number: " << c.courseNumber << endl;
        cout << "Course Title : " << c.courseTitle << endl;

        if (c.prereqNumbers.empty()) {
            cout << "Prerequisites: None" << endl;
        }
        else {
            cout << "Prerequisites: ";
            for (size_t i = 0; i < c.prereqNumbers.size(); ++i) {
                cout << c.prereqNumbers[i];
                if (i < c.prereqNumbers.size() - 1)
                    cout << ", ";
            }
            cout << endl;
        }
    }

    bool isDataLoaded() const { return dataLoaded; }

    void clearData() {
        courseTable.clear();
        dataLoaded = false;
    }
};

// This is my menu for the advising program.
void printMenu() {
    cout << "\n Welcome to the course planner." << endl;
    cout << "1. Load file data into the data structure." << endl;
    cout << "2. Print an alphanumeric list of all courses." << endl;
    cout << "3. Print a specific course." << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
}

int main() {
    CourseManager manager;
    int choice = 0;

    while (true) {
        printMenu();

        // Reads the user's menu choice safely.
        if (!(cin >> choice)) {
            // If a Non-integer input, it displays an error and consumes the rest of the line.
            cout << "Invalid input. Please enter a numeric menu option." << endl;
            cin.clear();
            string junk;
            getline(cin, junk); // Discards the invalid input line.
            continue;
        }

        // This will consume leftover newline so future getline will work properly.
        string leftover;
        getline(cin, leftover);

        if (choice == 1) {
			cout << "\nLoading data from CS 300 ABCU_Advising_Program_Input file." << endl;
            manager.loadFromFile();
        }
        else if (choice == 2) {
			cout << "\nHere is a sample schedule:" << endl;
            manager.printAllCoursesSorted();
        }
        else if (choice == 3) {
            cout << "What course do you want to know about? ";
            string courseNum;
            getline(cin, courseNum);
            courseNum = trim(courseNum);
            if (courseNum.empty()) {
                cout << "No course number entered. Please try again." << endl;
                continue;
            }
            for (char& ch : courseNum) {
                ch = toupper(static_cast<unsigned char>(ch));
            }
            manager.printCourseInfo(courseNum);
        }
        else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
            break;
        }
        else {
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}
