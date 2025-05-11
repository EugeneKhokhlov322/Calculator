#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

class Operation {
public:
    virtual ~Operation() = default;
    virtual double execute(double a, double b) = 0;
};

class Calculator {
private:
    Operation* operation;
    double memory = 0; // Додано поле пам'яті

public:
    void setOperation(Operation* op) {
        operation = op;
    }

    double calculate(double a, double b, bool log = false) {
        double result = operation->execute(a, b);
        if (log) {
            cout << "Logged: " << a << " op " << b << " = " << result << endl;
        }
        return result;
    }

    // Нові методи для роботи з пам'яттю
    void storeToMemory(double value) {
        memory = value;
    }

    double recallFromMemory() const {
        return memory;
    }
};

// Класи операцій з вбудованими тимчасовими змінними
class Addition : public Operation {
public:
    double execute(double a, double b) override {
        return a + b; // Вбудована тимчасова змінна
    }
};

class Division : public Operation {
public:
    double execute(double a, double b) override {
        if (b == 0) throw invalid_argument("Division by zero");
        return a / b; // Вбудована тимчасова змінна
    }
};

int main() {
    Calculator calc;
    Addition add;

    calc.setOperation(&add);
    cout << "10 + 5 = " << calc.calculate(10, 5, true) << endl;

    calc.storeToMemory(100);
    cout << "Memory: " << calc.recallFromMemory() << endl;

    return 0;
}