/*
 * ============================================================
 *  STUDENT GRADE CHECKER  –  Group 7
 *  Language : C++17
 *
 *  Data Structures Used:
 *    - queue<Student>  : enrollment/input order (FIFO)
 *    - vector<Student> : for sorting and display
 *
 *  Features:
 *    - Add students with marks for multiple subjects
 *    - Auto-calculate average, letter grade & GPA
 *    - Track performance across multiple terms
 *    - Display sorted: alphabetical | grade asc | grade desc
 *    - Class statistics
 * ============================================================
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>

using namespace std;

/* ── Constants ──────────────────────────────────────────────── */
const int MAX_SUBJECTS = 10;
const int MAX_TERMS    = 5;

/* ── Grade calculation ──────────────────────────────────────── */
string getGrade(float avg) {
    if (avg >= 90) return "A+";
    if (avg >= 85) return "A";
    if (avg >= 80) return "A-";
    if (avg >= 75) return "B+";
    if (avg >= 70) return "B";
    if (avg >= 65) return "B-";
    if (avg >= 60) return "C+";
    if (avg >= 55) return "C";
    if (avg >= 50) return "C-";
    if (avg >= 45) return "D";
    return "F";
}

float getGPA(float avg) {
    if (avg >= 90) return 4.0f;
    if (avg >= 85) return 4.0f;
    if (avg >= 80) return 3.7f;
    if (avg >= 75) return 3.3f;
    if (avg >= 70) return 3.0f;
    if (avg >= 65) return 2.7f;
    if (avg >= 60) return 2.3f;
    if (avg >= 55) return 2.0f;
    if (avg >= 50) return 1.7f;
    if (avg >= 45) return 1.0f;
    return 0.0f;
}

/* ── Term ───────────────────────────────────────────────────── */
struct Term {
    int            termNumber;
    vector<string> subjects;
    vector<float>  marks;
    float          average = 0.0f;
    string         grade   = "N/A";
    float          gpa     = 0.0f;

    void calculate() {
        if (marks.empty()) return;
        average = accumulate(marks.begin(), marks.end(), 0.0f) / marks.size();
        grade   = getGrade(average);
        gpa     = getGPA(average);
    }
};

/* ── Student ────────────────────────────────────────────────── */
struct Student {
    string       name;
    int          id;
    vector<Term> terms;

    float latestAverage() const {
        return terms.empty() ? -1.0f : terms.back().average;
    }
    string latestGrade() const {
        return terms.empty() ? "–" : terms.back().grade;
    }
    float latestGPA() const {
        return terms.empty() ? 0.0f : terms.back().gpa;
    }
};

/* ── I/O Helpers ────────────────────────────────────────────── */
void clearBuf() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string& prompt, int lo, int hi) {
    int v;
    while (true) {
        cout << prompt;
        if (cin >> v && v >= lo && v <= hi) { clearBuf(); return v; }
        cin.clear(); clearBuf();
        cout << "  [!] Enter a number between " << lo << " and " << hi << ".\n";
    }
}

float readFloat(const string& prompt, float lo, float hi) {
    float v;
    while (true) {
        cout << prompt;
        if (cin >> v && v >= lo && v <= hi) { clearBuf(); return v; }
        cin.clear(); clearBuf();
        cout << "  [!] Enter a value between " << lo << " and " << hi << ".\n";
    }
}

string readLine(const string& prompt) {
    string s;
    while (true) {
        cout << prompt;
        getline(cin, s);
        auto b = s.find_first_not_of(" \t");
        auto e = s.find_last_not_of(" \t\r\n");
        if (b != string::npos) { s = s.substr(b, e - b + 1); if (!s.empty()) return s; }
        cout << "  [!] Input cannot be empty.\n";
    }
}

/* ── Display ────────────────────────────────────────────────── */
void divider() { cout << "  " << string(56, '-') << "\n"; }

void printHeader() {
    cout << "\n";
    cout << "  ╔══════════════════════════════════════════════════════╗\n";
    cout << "  ║          STUDENT GRADE CHECKER  –  Group 7          ║\n";
    cout << "  ╚══════════════════════════════════════════════════════╝\n";
}

void printRow(int rank, const Student& s) {
    cout << "  " << setw(3) << rank << ". "
         << left << setw(22) << s.name
         << "ID:" << setfill('0') << setw(3) << s.id << setfill(' ');
    if (s.terms.empty()) { cout << "  (no terms yet)\n"; return; }
    const Term& t = s.terms.back();
    cout << "  Avg:" << fixed << setprecision(2) << setw(7) << t.average
         << "  Grade:" << left << setw(3) << t.grade
         << "  GPA:" << setprecision(1) << t.gpa
         << "  [T" << t.termNumber << "]\n";
}

void printDetail(const Student& s) {
    divider();
    cout << "  Student : " << s.name
         << "  (ID: " << setfill('0') << setw(3) << s.id << setfill(' ') << ")\n"
         << "  Terms   : " << s.terms.size() << "\n";
    for (const auto& t : s.terms) {
        cout << "\n  ┌─ Term " << t.termNumber << " ───────────────────────────────\n";
        for (size_t j = 0; j < t.subjects.size(); j++)
            cout << "  │  " << left << setw(25) << t.subjects[j]
                 << ": " << right << fixed << setprecision(2) << t.marks[j] << "\n";
        cout << "  │\n"
             << "  │  Average : " << fixed << setprecision(2) << t.average << "\n"
             << "  │  Grade   : " << t.grade << "\n"
             << "  │  GPA     : " << setprecision(1) << t.gpa << "\n"
             << "  └─────────────────────────────────────────\n";
    }
}

/* ── Main Application ───────────────────────────────────────── */
int main() {
    /*
     *  PRIMARY storage  : queue<Student>
     *    - Maintains enrollment/insertion order (FIFO)
     *    - New students pushed to the back
     *
     *  DISPLAY storage  : vector<Student>  (built on demand)
     *    - Copied from queue for sorting without disturbing queue order
     */
    queue<Student> enrollQueue;   // FIFO enrollment order
    int nextId = 1;

    /* Helper: find student in queue by name */
    auto findStudent = [&](const string& name) -> Student* {
        // We iterate a copy approach via a temp reference vector
        // (queue doesn't support direct iteration; we use a workaround)
        queue<Student> tmp = enrollQueue;
        while (!tmp.empty()) {
            if (tmp.front().name == name) {
                // Return pointer into original queue via linear scan
                // Note: std::queue wraps std::deque; we rebuild to get pointer
                break;
            }
            tmp.pop();
        }
        // Rebuild as vector for pointer access
        return nullptr; // handled below via vector rebuild
    };
    (void)findStudent; // suppress unused warning; logic handled inline below

    /* Convert queue to vector (non-destructive) */
    auto toVector = [&]() -> vector<Student> {
        vector<Student> v;
        queue<Student> tmp = enrollQueue;
        while (!tmp.empty()) { v.push_back(tmp.front()); tmp.pop(); }
        return v;
    };

    /* Rebuild queue from modified vector */
    auto fromVector = [&](const vector<Student>& v) {
        queue<Student> q;
        for (const auto& s : v) q.push(s);
        enrollQueue = q;
    };

    int choice;
    while (true) {
        printHeader();
        cout << "  Students enrolled: " << enrollQueue.size() << "\n\n"
             << "  [1] Add student\n"
             << "  [2] Remove student\n"
             << "  [3] Enter marks (new term)\n"
             << "  [4] View student detail\n"
             << "  [5] Display all  →  Alphabetical (A-Z)\n"
             << "  [6] Display all  →  Grade ascending\n"
             << "  [7] Display all  →  Grade descending\n"
             << "  [8] Display all  →  Enrollment order (queue)\n"
             << "  [9] Class statistics\n"
             << "  [0] Exit\n\n"
             << "  Choice: ";

        if (!(cin >> choice)) { cin.clear(); clearBuf(); continue; }
        clearBuf();

        /* ── 1. Add student ─────────────────────────────────── */
        if (choice == 1) {
            string name = readLine("\n  Enter student name: ");
            // Check duplicate
            vector<Student> v = toVector();
            bool dup = false;
            for (const auto& s : v) if (s.name == name) { dup = true; break; }
            if (dup) { cout << "  [!] \"" << name << "\" already exists.\n"; }
            else {
                Student s; s.name = name; s.id = nextId++;
                enrollQueue.push(s);
                cout << "  [✓] Added \"" << name << "\" (ID "
                     << setfill('0') << setw(3) << s.id << setfill(' ') << ").\n";
            }
        }

        /* ── 2. Remove student ──────────────────────────────── */
        else if (choice == 2) {
            string name = readLine("\n  Enter student name to remove: ");
            vector<Student> v = toVector();
            auto it = find_if(v.begin(), v.end(),
                              [&](const Student& s){ return s.name == name; });
            if (it == v.end()) { cout << "  [!] \"" << name << "\" not found.\n"; }
            else {
                cout << "  [✓] Removed \"" << it->name << "\" (ID "
                     << setfill('0') << setw(3) << it->id << setfill(' ') << ").\n";
                v.erase(it);
                fromVector(v);
            }
        }

        /* ── 3. Enter marks ─────────────────────────────────── */
        else if (choice == 3) {
            string name = readLine("\n  Enter student name: ");
            vector<Student> v = toVector();
            auto it = find_if(v.begin(), v.end(),
                              [&](const Student& s){ return s.name == name; });
            if (it == v.end()) { cout << "  [!] Student not found.\n"; }
            else if ((int)it->terms.size() >= MAX_TERMS) {
                cout << "  [!] Max terms (" << MAX_TERMS << ") reached.\n";
            } else {
                Term t;
                t.termNumber = (int)it->terms.size() + 1;
                int n = readInt("  Number of subjects (1-" +
                                to_string(MAX_SUBJECTS) + "): ", 1, MAX_SUBJECTS);
                for (int j = 0; j < n; j++) {
                    string subj = readLine("  Subject " + to_string(j+1) + " name: ");
                    float  mark = readFloat("  Mark for " + subj + " (0-100): ", 0, 100);
                    t.subjects.push_back(subj);
                    t.marks.push_back(mark);
                }
                t.calculate();
                it->terms.push_back(t);
                fromVector(v);
                cout << "\n  [✓] Term " << t.termNumber << " saved."
                     << "  Avg: " << fixed << setprecision(2) << t.average
                     << "  Grade: " << t.grade
                     << "  GPA: "   << setprecision(1) << t.gpa << "\n";
            }
        }

        /* ── 4. View student detail ─────────────────────────── */
        else if (choice == 4) {
            string name = readLine("\n  Enter student name: ");
            vector<Student> v = toVector();
            auto it = find_if(v.begin(), v.end(),
                              [&](const Student& s){ return s.name == name; });
            if (it == v.end()) cout << "  [!] Student not found.\n";
            else printDetail(*it);
        }

        /* ── 5-8. Display sorted ────────────────────────────── */
        else if (choice >= 5 && choice <= 8) {
            vector<Student> v = toVector();
            if (v.empty()) { cout << "  [!] No students enrolled.\n"; }
            else {
                if (choice == 5) {
                    sort(v.begin(), v.end(),
                         [](const Student& a, const Student& b){ return a.name < b.name; });
                    cout << "\n  Sorted: Alphabetical (A → Z)\n";
                } else if (choice == 6) {
                    sort(v.begin(), v.end(),
                         [](const Student& a, const Student& b){
                             return a.latestAverage() < b.latestAverage(); });
                    cout << "\n  Sorted: Grade Ascending (lowest → highest)\n";
                } else if (choice == 7) {
                    sort(v.begin(), v.end(),
                         [](const Student& a, const Student& b){
                             return a.latestAverage() > b.latestAverage(); });
                    cout << "\n  Sorted: Grade Descending (highest → lowest)\n";
                } else {
                    cout << "\n  Enrollment Order (Queue – FIFO)\n";
                }
                divider();
                cout << "  " << setw(4) << "#"
                     << "  " << left << setw(22) << "Name"
                     << "ID    Average  Grade  GPA   Term\n";
                divider();
                for (int i = 0; i < (int)v.size(); i++)
                    printRow(i + 1, v[i]);
                divider();
            }
        }

        /* ── 9. Class statistics ────────────────────────────── */
        else if (choice == 9) {
            vector<Student> v = toVector();
            if (v.empty()) { cout << "  [!] No students enrolled.\n"; }
            else {
                int   counted = 0;
                float total = 0, high = -1, low = 101;
                string topName, botName;
                for (const auto& s : v) {
                    float avg = s.latestAverage();
                    if (avg < 0) continue;
                    total += avg; counted++;
                    if (avg > high) { high = avg; topName = s.name; }
                    if (avg < low)  { low  = avg; botName = s.name; }
                }
                divider();
                cout << "  CLASS STATISTICS\n";
                divider();
                cout << "  Total students : " << v.size() << "\n"
                     << "  With grades    : " << counted  << "\n";
                if (counted > 0)
                    cout << fixed << setprecision(2)
                         << "  Class average  : " << total / counted << "\n"
                         << "  Highest avg    : " << high << "  (" << topName << ")\n"
                         << "  Lowest  avg    : " << low  << "  (" << botName << ")\n";
                divider();
            }
        }

        /* ── 0. Exit ────────────────────────────────────────── */
        else if (choice == 0) {
            cout << "\n  Goodbye!\n\n";
            break;
        } else {
            cout << "  [!] Invalid choice. Enter 0-9.\n";
        }

        cout << "\n  Press ENTER to continue...";
        clearBuf();
    }

    return 0;
}
