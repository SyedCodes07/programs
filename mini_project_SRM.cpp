#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>
using namespace std;
 
const int SUBJECTS = 5;
const string DATA_FILE = "results.txt";
 
// Custom exception for invalid marks (Week 9)
class InvalidMarkException : public exception {
    string msg;
public:
    InvalidMarkException(const string &m) : msg(m) {}
    const char* what() const noexcept override { return msg.c_str(); }
};
 
// Abstract base class with pure virtual grade() (Week 8)
class Result {
protected:
    vector<int> marks;
public:
    Result(const vector<int> &m) : marks(m) {}
    virtual ~Result() {}
    double percentage() const {
        int total = 0;
        for (int m : marks) total += m;
        return 100.0 * total / (marks.size() * 100.0);
    }
    bool passed() const {
        return all_of(marks.begin(), marks.end(), [](int m) { return m >= 40; });
    }
    virtual string grade() const = 0;             // pure virtual
    virtual string category() const { return "Result"; }
    virtual void display() const {                // virtual, overridable
        cout << "  Marks: ";
        for (int m : marks) cout << m << " ";
        cout << "| Percentage: " << percentage() << "% | Grade: " << grade() << "\n";
    }
    virtual void save(ostream &os) const {
        for (int m : marks) os << "," << m;
    }
};
 
// Derived class: grades by percentage bands (inheritance + override)
class ExamResult : public Result {
public:
    ExamResult(const vector<int> &m) : Result(m) {}
    string grade() const override {
        if (!passed()) return "F";
        double p = percentage();
        if (p >= 85) return "A";
        if (p >= 70) return "B";
        if (p >= 55) return "C";
        return "D";
    }
    string category() const override { return "Exam"; }
};
 
class Student {
    string name, usn;
    shared_ptr<Result> result;            // polymorphic result object
public:
    Student(const string &n, const string &u, shared_ptr<Result> r)
        : name(n), usn(u), result(r) {}
    const string& getUsn() const { return usn; }
    const string& getName() const { return name; }
    double percentage() const { return result->percentage(); }
    bool passed() const { return result->passed(); }
    void display() const {
        cout << usn << "  " << name << " [" << result->category() << "]\n";
        result->display();
    }
    void save(ostream &os) const {
        os << usn << "," << name;
        result->save(os);
        os << "\n";
    }
};
 
vector<Student> students;
 
// Validate one mark from text (Week 9 exceptions, Week 3 validation)
int parseMark(const string &text) {
    size_t used = 0;
    int value;
    try {
        value = stoi(text, &used);
    } catch (const exception &) {
        throw InvalidMarkException("'" + text + "' is not a number");
    }
    if (used != text.size())
        throw InvalidMarkException("'" + text + "' has extra characters");
    if (value < 0 || value > 100)
        throw InvalidMarkException("mark " + to_string(value) + " must be 0-100");
    return value;
}
 
string prompt(const string &question) {
    cout << question;
    string line;
    if (!getline(cin, line)) throw runtime_error("end of input");
    return line;
}
 
void addStudent() {
    string usn = prompt("USN: ");
    if (any_of(students.begin(), students.end(),
               [&](const Student &s) { return s.getUsn() == usn; }))
        throw runtime_error("USN " + usn + " already exists");
    string name = prompt("Name: ");
 
    vector<int> marks;
    for (int i = 1; i <= SUBJECTS; ++i) {
        while (true) {                      // re-ask until the mark is valid
            try {
                marks.push_back(parseMark(prompt("Subject " + to_string(i) + " mark: ")));
                break;
            } catch (const InvalidMarkException &e) {
                cout << "  Invalid: " << e.what() << ". Try again.\n";
            }
        }
    }
    students.emplace_back(name, usn, make_shared<ExamResult>(marks));
    cout << "Student added.\n";
}
 
void displayAll() {
    if (students.empty()) { cout << "No records.\n"; return; }
    for_each(students.begin(), students.end(), [](const Student &s) { s.display(); });
}
 
void showPassed() {
    vector<Student> passedList;
    copy_if(students.begin(), students.end(), back_inserter(passedList),
            [](const Student &s) { return s.passed(); });        // lambda filter
    sort(passedList.begin(), passedList.end(),
         [](const Student &a, const Student &b) { return a.percentage() > b.percentage(); });
    cout << "Passed students (sorted by percentage): " << passedList.size() << "\n";
    for_each(passedList.begin(), passedList.end(), [](const Student &s) { s.display(); });
}
 
void saveFile() {
    ofstream out(DATA_FILE);
    if (!out) throw runtime_error("cannot open " + DATA_FILE + " for writing");
    for (const Student &s : students) s.save(out);
    cout << "Saved " << students.size() << " record(s) to " << DATA_FILE << ".\n";
}
 
void loadFile() {
    ifstream in(DATA_FILE);
    if (!in) throw runtime_error("cannot open " + DATA_FILE + " (save first)");
    students.clear();
    string line;
    int lineNo = 0, loaded = 0;
    while (getline(in, line)) {
        ++lineNo;
        if (line.empty()) continue;
        try {
            stringstream ss(line);
            string usn, name, field;
            getline(ss, usn, ',');
            getline(ss, name, ',');
            vector<int> marks;
            while (getline(ss, field, ',')) marks.push_back(parseMark(field));
            if ((int)marks.size() != SUBJECTS) throw runtime_error("wrong number of marks");
            students.emplace_back(name, usn, make_shared<ExamResult>(marks));
            ++loaded;
        } catch (const exception &e) {
            cout << "  Skipped line " << lineNo << ": " << e.what() << "\n";
        }
    }
    cout << "Loaded " << loaded << " record(s).\n";
}
 
int main() {
    while (true) {
        cout << "\n1 Add  2 Display all  3 Passed list  4 Save  5 Load  0 Exit\n";
        string choice;
        try {
            choice = prompt("Choice: ");
            if (choice == "1") addStudent();
            else if (choice == "2") displayAll();
            else if (choice == "3") showPassed();
            else if (choice == "4") saveFile();
            else if (choice == "5") loadFile();
            else if (choice == "0") break;
            else cout << "Unknown option.\n";
        } catch (const exception &e) {
            if (!cin) break;
            cout << "Error: " << e.what() << "\n";
        }
    }
    cout << "Goodbye.\n";
    return 0;
}
