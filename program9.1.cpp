
#include <iostream>
#include <exception>
#include <string>
using namespace std;

class InvalidAgeException : public exception {
    string msg;

public:
    InvalidAgeException(int age)
        : msg("Invalid age: " + to_string(age)) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }
};

void registerUser(int age) {
    if (age < 0)
        throw InvalidAgeException(age);

    if (age < 18)
        throw string("Too Young to vote");

    cout << "Registered (age " << age << ")" << endl;
}

int main() {
    int ages[] = {25, 15, -3};

    for (int age : ages) {
        try {
            registerUser(age);
        }
        catch (const InvalidAgeException& e) {
            cout << "[ERR] " << e.what() << endl;
        }
        catch (const string& msg) {
            cout << "[WARN] " << msg << endl;
        }
        catch (...) {
            cout << "[ERR] Unknown error\n";
        }
    }

    return 0;
}
